#include "rectangle_controller.h"

RectangleController::RectangleController() {
	dragged = false;
}

RectangleController::RectangleController(const RectangleController& that) {
	// this actually don't make sense, but we'll let it slide for now
	leftX = that.leftX;
	topY = that.topY;
	width = that.width;
	height = that.height;
	dragged= that.dragged;
}

RectangleController& RectangleController::operator= (const RectangleController& that) {
	// this actually don't make sense, but we'll let it slide for now
	if (this != &that) {
		leftX = that.leftX;
		topY = that.topY;
		width = that.width;
		height = that.height;
		dragged= that.dragged;
	}
	return *this;
}

RectangleController::~RectangleController() {}

void RectangleController::leftDown(int x, int y) {
	dragged = true;
	leftX = x;
	topY = y;
	std::cout << "leftDown triggered on (" << x << "," << y << ")" << std::endl;
}

void RectangleController::leftUp(int x, int y) {
	dragged = false;
	width = x - leftX;
	height = y - topY;

	// rectangle creation goes here..

	std::cout << "Created rectangle at (" << leftX << "," << topY << ") ";
	std::cout << "with size (" << width << "," << height << ")." << std::endl;
}

void RectangleController::movement(int x, int y) {
	// rectangle construction animation goes here..
	std::cout << "new location (" << x << "," << y << ")" << std::endl;
}
