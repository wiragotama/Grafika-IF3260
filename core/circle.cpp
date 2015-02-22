#include "circle.h"

Circle::Circle(Point midPoint, int radius) {
	this->midPoint = midPoint;
	this->radius = radius;
}

Circle::~Circle() {

}

Circle& Circle::operator=(const Circle& circle) {
	setMidPoint(circle.midPoint);
	setRadius(circle.radius);
}

void Circle::setMidPoint(const Point midPoint) {
	this->midPoint = midPoint;
}

void Circle::setRadius(const int radius) {
	this->radius = radius;
}

void Circle::move(const int dx, const int dy) {
	this->midPoint.move(dx, dy);
}

void Circle::moveDown(const int d) {
	this->midPoint.moveDown(d);
}

void Circle::drawFull(Canvas *canvas, uint32_t color) {
	int x = this->radius;
	int y = 0;
	int radiusError = 1-x;
	int x0 = this->midPoint.getAbsis();
	int y0 = this->midPoint.getOrdinat();
 
	while(x >= y) {
		canvas->putPixelColor(x+x0, y+y0, color);
		canvas->putPixelColor(y+x0, x+y0, color);
		canvas->putPixelColor(-x+x0, y+y0, color);
		canvas->putPixelColor(-y+x0, x+y0, color);
		canvas->putPixelColor(-x+x0, -y+y0, color);
		canvas->putPixelColor(-y+x0, -x+y0, color);
		canvas->putPixelColor(x+x0, -y+y0, color);
	    canvas->putPixelColor(y+x0, -x+y0, color);
	    y++;
		if (radiusError<0) {
			radiusError += 2 * y + 1;
		} else {
			x--;
			radiusError += 2 * (y - x) + 1;
		}
	}
}

void Circle::drawSemiTop(Canvas *canvas, uint32_t color) {
	int x = this->radius;
	int y = 0;
	int radiusError = 1-x;
	int x0 = this->midPoint.getAbsis();
	int y0 = this->midPoint.getOrdinat();
 
	while(x >= y) {
		// canvas->putPixelColor(x+x0, y+y0, color);
		// canvas->putPixelColor(y+x0, x+y0, color);
		// canvas->putPixelColor(-x+x0, y+y0, color);
		// canvas->putPixelColor(-y+x0, x+y0, color);
		canvas->putPixelColor(-x+x0, -y+y0, color);
		canvas->putPixelColor(-y+x0, -x+y0, color);
		canvas->putPixelColor(x+x0, -y+y0, color);
	    canvas->putPixelColor(y+x0, -x+y0, color);
	    y++;
		if (radiusError<0) {
			radiusError += 2 * y + 1;
		} else {
			x--;
			radiusError += 2 * (y - x) + 1;
		}
	}
}

int Circle::getRadius() {
	return radius;
}

Point Circle::getMidPoint() {
	return midPoint;
}
