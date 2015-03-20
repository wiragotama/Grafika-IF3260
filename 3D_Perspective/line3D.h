#ifndef LINE3D_H
#define LINE3D_H

#include "point3D.h"
#include <iostream>
#include <vector>
using namespace std;

class Line3D {
	public :
		Line3D();
		Line3D(Point3D P1,Point3D P2);
		Line3D(const Line3D& l); //cctor
		virtual Line3D& operator= (const Line3D& l); //assignment
		~Line3D();

		Point3D getPointOne() const;
		Point3D getPointTwo() const;
		vector<Point3D> getPoints() const;
		
		void setPointOne(Point3D P);
		void setPointTwo(Point3D P);
		
	private :
		vector<Point3D> points;
};

#endif
