#ifndef CUBE_H
#define CUBE_H

#include "line3D.h"
#include <iostream>
#include <vector>
using namespace std;

class Cube{
	public:
		Cube();
		Cube(vector<Line3D> sisi);
		Cube(const Cube& kubus);
		virtual Cube& operator= (const Cube& kubus);
		~Cube();
		
		vector<Point3D> getSide(int i);
		void setSide(int i,Line3D satu_sisi);
		vector<Line3D> getAllSide() const;
	
	private:
		vector<Line3D> edges;
};

#endif
