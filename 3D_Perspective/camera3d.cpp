#include "camera3d.h"

const Point3D Camera3D::standard_axes[CAMERA3D_NUM_AXES] = { Point3D(1, 0, 0),
	Point3D(0, 1, 0), Point3D(0, 0, 1) };

Camera3D::Camera3D() {
	plane_distance = PLANE_DISTANCE_FROM_ORIGIN;
	convergent_point_distance = 10;

	for (int i = 0; i < CAMERA3D_NUM_AXES; i++) {
		axes[i] = standard_axes[i];
	}
}

Camera3D::~Camera3D() {
}

void Camera3D::recalculate_axis() {
	Matrix m1 = Matrix::get3DRotationX(polar - M_PI/2);
	Matrix m2 = Matrix::get3DRotationY(azimuth);

	Matrix T(3, 4);
	for (int i = 0; i < 3; i++) {
		T.setElement(i, 0, standard_axes[i].getX());
		T.setElement(i, 1, standard_axes[i].getY());
		T.setElement(i, 2, standard_axes[i].getZ());
		T.setElement(i, 3, 1);
	}

	Matrix Tr = T.multiply(m1).multiply(m2);

	for (int i = 0; i < 3; i++) {
		axes[i].setX(Tr.getElement(i, 0));
		axes[i].setY(Tr.getElement(i, 1));
		axes[i].setZ(Tr.getElement(i, 2));
	}
	
}

void Camera3D::setAzimuth(double radians) {
	azimuth = radians;
	recalculate_axis();
}

void Camera3D::setPolar(double radians) {
	polar = radians;
	recalculate_axis();
}

double Camera3D::getAzimuth(){
	return azimuth;
}

double Camera3D::getPolar(){
	return polar;
}

std::vector<Point3D> Camera3D::project_points(const std::vector<Point3D>& points,
	double& midPoint_distance) const
{
	Matrix T(3);
	for (int i = 0; i < 3; i++) {
		T.setElement(0, i, axes[i].getX() );
		T.setElement(1, i, axes[i].getY() );
		T.setElement(2, i, axes[i].getZ() );
	}

	Matrix P( points.size(), 3);
	for (int i = 0; i < P.getRow(); i++) {
		P.setElement(i, 0, points[i].getX() );
		P.setElement(i, 1, points[i].getY() );
		P.setElement(i, 2, points[i].getZ() );
	}

	Matrix Tr = P.multiply(T);
	std::vector<Point3D> t_points( P.getRow(), Point3D() );
	for (int i = 0; i < P.getRow(); i++) {
		t_points[i].setX( Tr.getElement(i, 0) );
		t_points[i].setY( Tr.getElement(i, 1) );
		t_points[i].setZ( Tr.getElement(i, 2) );
	}

	// assume that the vector is already aligned
	std::vector<Point3D> result(points.size(), Point3D());

	double base_distance = convergent_point_distance - plane_distance;
	int idx = 0;
	midPoint_distance = 0;
	for (std::vector<Point3D>::const_iterator it_point = t_points.begin();
		it_point != t_points.end(); it_point++)
	{
		result[idx].setX( (convergent_point_distance - it_point->getZ())/
			base_distance * it_point->getX() );
		result[idx].setY( (convergent_point_distance - it_point->getZ())/
			base_distance * it_point->getY() );
		result[idx].setZ( plane_distance );
		midPoint_distance += it_point->getZ();
		idx++;
	}
	midPoint_distance /= P.getRow();

	return result;
}

void Camera3D::printAxes(){
	printf("Axes: ");
	for(int i=0; i<CAMERA3D_NUM_AXES; i++){
		Point3D p = axes[i];
		printf("(%lf %lf %lf) ", p.getX(), p.getY(), p.getZ());
	}
	printf("\n");
}
