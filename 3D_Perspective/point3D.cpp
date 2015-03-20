#include "point3D.h"

Point3D::Point3D() { //constructor default tanpa parameter
	x = 0;
	y = 0;
	z = 0;
}

Point3D::Point3D(double new_x, double new_y, double new_z) { //constructor dengan parameter
	x = new_x;
	y = new_y;
	z = new_z;
}

Point3D::Point3D(const Point3D& p) { //copy constructor
	this->x = p.getX();
	this->y = p.getY();
	this->z = p.getZ();
}

Point3D::Point3D& operator= (const Point3D& p) { //assignment
	this->x = p.getX();
	this->y = p.getY();
	this->z = p.getZ();
	return *this;
}

Point3D::~Point3D() { //destructor
}

double Point3D::getX() const {
	return x;
}

double Point3D::getY() const {
	return y;
}

double Point3D::getZ() const {
	return z;
}

void Point3D::setX(double x) {
	this->x = x;
}

void Point3D::setY(double y) {
	this->y = y;
}

void Point3D::setZ(double z) {
	this->z = z;
}

void Point3D::printInfo() {
	printf("%.2lf %.2lf %.2lf\n", x, y, z);
}

bool Point3D::isEqual(Point3D p) const {
	return (x==p.getX() && y==p.getY() && z==p.getZ());
}
