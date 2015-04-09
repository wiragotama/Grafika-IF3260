#ifndef POLYGON_H
#define POLYGON_H

#include <stdint.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "point.h"
#include "line.h"

using namespace std;

class Polygon {
	public:
		Polygon(vector<Point> nodes);
		
		vector<Point> getPoints() const;
		vector<Line> getLines() const;
		
		void draw(Canvas *canvas, uint32_t color);
		void drawPersistent(Canvas *canvas, uint32_t color);
		void drawfill(Canvas *canvas, uint32_t color);
		void drawfillPersistent(Canvas *canvas, uint32_t color);
		
		double getMinX();
		double getMaxX();
		double getMinY();
		double getMaxY();
	
	private:
		vector<Point> nodes;
};

#endif
