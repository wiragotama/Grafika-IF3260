#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "canvas.h"
#include <vector>
#include <cmath>
#include <cassert>


class Line {
	public :
		Line(Point P1, Point P2);

		Point getPointOne();
		Point getPointTwo();

		void setPointOne(Point P);
		void setPointTwo(Point P);

		void draw(Canvas *canvas, int thickness, uint32_t color);

	private :
		Point point[2];
};

#endif
