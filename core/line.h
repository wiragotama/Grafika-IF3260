#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "canvas.h"
#include "header.h"
#include <vector>
#include <cmath>
#include <cassert>

#define STRAIGHT_LINE 0
#define DASHED_LINE 1

class Line {
	public :
		Line(Point P1, Point P2);
		~Line();

		Point getPointOne();
		Point getPointTwo();

		void setPointOne(Point P);
		void setPointTwo(Point P);

		void draw(Canvas *canvas, int thickness, uint32_t color);
		void drawBackground(Canvas *canvas, int thickness, uint32_t color);
		void drawCurve(Canvas *canvas, int thickness, uint32_t color);
		void drawCurveBackground(Canvas *canvas, int thickness, uint32_t color);
		/* Move on screen */
		void moveRight(int d);
		void moveLeft(int d);
		void moveUp(int d);
		void moveDown(int d);
		void move(int dx, int dy);
		Point* getIntersectionPointWith(Line);
		int getDifXInVector() const;
		int getDifYInVector() const;
	private :
		bool isIntersectWith(Line);
		bool onSegment(Point);
			
		Point point[2];
};

#endif
