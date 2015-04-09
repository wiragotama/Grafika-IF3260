#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdint.h>
#include <cmath>
#include "point.h"
#include "line.h"

using namespace std;

class Circle {
	public:
		Circle(double a, double b, double r);
		
		void drawfill(Canvas *canvas, uint32_t color);
		
	private:
		double a,b,r;
};

#endif
