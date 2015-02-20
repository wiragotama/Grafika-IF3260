#ifndef CIRCLE_H
#define CIRCLE_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/point.h"

class Circle {
	public:
		Circle(Point midPoint, int radius);
		~Circle();
		virtual Circle& operator= (const Circle& circle);
		void setMidPoint(const Point midPoint);
		void setRadius(const int radius);
		void move(const int, const int);
		void moveDown(const int);
		void drawFull(Canvas *canvas, uint32_t color);
		void drawSemiTop(Canvas *canvas, uint32_t color);

	private:
		Point midPoint;
		int radius;
};

#endif