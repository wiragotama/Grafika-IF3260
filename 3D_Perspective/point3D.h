#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

class Point3D {
	public :
		Point3D(); //constructor default tanpa parameter
		Point3D(double new_x, double new_y, double new_z); //constructor dengan parameter
		Point3D(const Point3D& p); //copy constructor
		virtual Point3D& operator= (const Point3D& p); //assignment
		~Point3D(); //destructor
		
		double getX() const;
		double getY() const;
		double getZ() const;
		void setX(double x);
		void setY(double y);
		void setZ(double z);
		
        void printInfo();
        
        bool isEqual(Point3D p) const;
		
	private :
		double x;
		double y;
		double z;
};

#endif
