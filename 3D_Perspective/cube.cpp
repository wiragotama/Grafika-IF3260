#include "cube.h"

/* The cube is from z+ axis with x+ to the right and y+ to the top */
Cube::Cube() {
	_init(2); // default side is 2
}

Cube::Cube(double side) {
	_init(side);
}

Cube::Cube(const Cube& kubus) {
	vertexes = kubus.vertexes;
}

Cube& Cube::operator= (const Cube& kubus) {
	if (this != &kubus){
		vertexes = kubus.vertexes;
	}
	return *this;
}

Cube::~Cube() {}

void Cube::_init(double side) {
	/* set the vertexes of the cube programatically
	 * the first bit represent the minus sign of x
	 * the second bit represent the minus sign of y
	 * the third bir represent the minus sign of z */

	double half = side/2;

	vertexes.resize(8, Point3D());
	for (int i = 0; i < 8; i++) {
		vertexes[i].setX( -1 * ((i >> 2) & 1) * half );
		vertexes[i].setY( -1 * ((i >> 1) & 1) * half );
		vertexes[i].setZ( -1 * (   i     & 1) * half );
	}
}

std::vector<Point3D> Cube::getSide(int idx) {
	/* get side by index
	 * 0 : x-y plane z-positive
	 * 1 : x-y plane z-negative
	 * 2 : y-z plane x-positive
	 * 3 : y-z plane x-negative
	 * 4 : x-z plane y-positive
	 * 5 : x-z plane y-negative */

	if (idx < 0 || idx >= 6)
		throw NO_SUCH_SIDE;

	std::vector<Point3D> result(4, Point3D());

	switch (idx) {
	case 0:
		for (int i = 0; i < 4; i++) {
			result[i] = vertexes[i << 1];
		}
		break;
	case 1:
		for (int i = 0; i < 4; i++) {
			result[i] = vertexes[1 | i << 1];
		}
		break;
	case 2:
		for (int i = 0; i < 4; i++) {
			result[i] = vertexes[i];
		}
		break;
	case 3:
		for (int i = 0; i < 4; i++) {
			result[i] = vertexes[4 | i];
		}
		break;
	case 4:
		for (int i = 0; i < 4; i++) {
			result[i] = vertexes[ ((i & 2) << 1) | (i & 1) ];
		}
		break;
	case 5:
		for (int i = 0; i < 4; i++) {
			result[i] = vertexes[ 2 | ((i & 2) << 1) | (i & 1) ];
		}
		break;
	}

	return result;
}

std::vector< std::pair<double, std::vector<Point3D> > > Cube::project_sides(const Camera3D& camera) {
	std::vector< std::pair<double, std::vector<Point3D> > > result;
	result.resize(6);

	for (int i = 0; i < 6; i++) {
		std::vector<Point3D> raw = getSide(i);
		result[i].second = camera.project_points(raw, result[i].first);
	}
	sort(result.begin(), result.end());

	return result;
}
