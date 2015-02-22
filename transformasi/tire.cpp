#include "tire.h"

Tire::Tire(Point midPoint, int radius) : Circle(midPoint, radius) {
	startBounce = false;
	bounceHeight = 300;
	bounceUp = true;
}

Tire::~Tire() {
}

Point Tire::getBottomPosition() {
	Point temp = Circle::getMidPoint();
	temp.move(0, Circle::getRadius());
	return temp;
}
void Tire::bounce() {
	if (bounceUp) {
		if (Circle::getMidPoint().getOrdinat() > bounceHeight) {
			Circle::move(1,-2);
		}
		else { 
			bounceUp = false;
			bounceHeight += 10;
		}
	}
	else {
		if (getBottomPosition().getOrdinat() <= 400) {
			Circle::move(1,2);
		}
		else bounceUp = true;
	}
}

void Tire::draw(Canvas *canvas, uint32_t color) {
	Circle::drawFull(canvas, color);
}

int Tire::getBounceHeight() {
	return bounceHeight;
}
