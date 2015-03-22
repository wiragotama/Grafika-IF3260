#ifndef CAMERA3D_H
#define CAMERA3D_H

#include "point3D.h"
#include "matrix.h"

#define CAMERA3D_NUM_AXES 3
#define PLANE_DISTANCE_FROM_ORIGIN 2
// ^ because our cube is centered at origin and have side length of 2

class Camera3D {
	public:
	Camera3D();
	Camera3D(const Camera3D&);
	Camera3D& operator= (const Camera3D&);
	~Camera3D();

	std::vector<Point3D> project_points(const std::vector<Point3D>&, double&) const;

	void setAzimuth(double);
	void setPolar(double);
	void recalculate_axis();

	private:
	Point3D axes[CAMERA3D_NUM_AXES];

	/* initially, we see the cube from the positive z-axis, viewing at it as if
	 * positive x-axis to the right and positive y-axis to top */
	double azimuth,
		/* radians from right hand rule against positive y-axis */
		polar;
		/* radians from the positive y-axis */

	double plane_distance, convergent_point_distance;

	static const Point3D standard_axes[CAMERA3D_NUM_AXES];
};

#endif
