#ifndef POLYGON_H
#define POLYGON_H

#include <stdint.h>
#include <vector>
#include <cstdlib>
#include "point.h"
#include "line.h"

using namespace std;

class Polygon {
	public:
		Polygon(vector<Point> nodes);
		~Polygon();
		Polygon(const Polygon& poly);
		Polygon& operator=(const Polygon& ply);
		
		vector<Point> getPoints() const;
		vector<Line> getLines() const; 
		
	private:
		vector<Point> nodes;
		uint32_t* color;
};

#endif
