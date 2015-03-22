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
		
		vector<Point> getPoints() const;
		vector<Line> getLines() const;
		
		void draw(Canvas *canvas, uint32_t color);
		
	private:
		vector<Point> nodes;
};

#endif
