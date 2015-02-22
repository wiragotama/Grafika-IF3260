#include "tire.h"

Tire::Tire() {
}

Tire::~Tire() {
}

void Tire::draw()
void Tire::move(int dx, int dy)
void Tire::bounce()
void Tire::setPosition() {
	
}

void Tire::setColor(uint32_t color) {
	this->color = color;
}

Point Tire::getCenterPoint() {
	return this->centerPoint;
}

Point Tire::getBottomPosition() {
	return this->bottomPosition;
}

Point Tire::getTopPosition() {
	return this->topPosition;
}

int Tire::getHeight() {//bounce height
	return bounceHeight;
}

int Tire::getWidth() { //tire diameter
	return radius*2;
}

uint32_t Tire::getColor() {
	return color;
}
