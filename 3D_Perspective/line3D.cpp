#include "line3D.h"

Line3D::Line3D()
{
	Point3D temp;
	points.push_back(temp);
	points.push_back(temp);
}

Line3D::Line3D(Point3D P1,Point3D P2)
{	
	this->points.push_back(P1);
	this->points.push_back(P2);
}

Line3D::Line3D(const Line3D& l)//cctor
{	
	this->points.push_back(l.getPointOne());
	this->points.push_back(l.getPointTwo());
}

Line3D& Line3D::operator= (const Line3D& l) //assignment
{
	if (this->points.size() != 0) {
		this->points[0] = l.getPointOne();
		this->points[1] = l.getPointTwo();
	}
	return *this;
}

Line3D::~Line3D()
{
	points.clear();
}

Point3D Line3D::getPointOne() const
{
	return points[0];
}

Point3D Line3D::getPointTwo() const{
	return points[1];
}

vector<Point3D> Line3D::getPoints() const
{
	return points;
}

void Line3D::setPointOne(Point3D P)
{
	this->points[0] = P;
}

void Line3D::setPointTwo(Point3D P)
{
	this->points[1] = P;
}
