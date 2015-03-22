#ifndef CUBE_H
#define CUBE_H

#include "camera3d.h"
#include "point3D.h"
#include <algorithm>
#include <vector>

class Cube {
	/* The cube is from z+ axis with x+ to the right and y+ to the top */
	public:
		Cube();
		Cube(double side);
		Cube(const Cube& kubus);
		virtual Cube& operator= (const Cube& kubus);
		~Cube();

		std::vector<Point3D> getSide(int i);
		std::vector< std::pair<double, std::vector<Point3D> > >
			project_sides(const Camera3D& );
			
		void printInfo();

		static const int NO_SUCH_SIDE = 1;

	private:
		void _init(double side);

		std::vector<Point3D> vertexes;
};

#endif
