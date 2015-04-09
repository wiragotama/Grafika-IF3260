#include "rectangle_controller.h"

RectangleController::RectangleController(Canvas* canvas) : MouseListener(canvas) {
	// MouseListener::MouseListener(canvas);
	dragged = false;
	poly = NULL;
}

RectangleController::RectangleController(const RectangleController& that) : MouseListener (canvas) {
	// this actually don't make sense, but we'll let it slide for now
	leftX = that.leftX;
	topY = that.topY;
	width = that.width;
	height = that.height;
	dragged= that.dragged;
	canvas = that.canvas;
}

RectangleController& RectangleController::operator= (const RectangleController& that) {
	// this actually don't make sense, but we'll let it slide for now
	if (this != &that) {
		leftX = that.leftX;
		topY = that.topY;
		width = that.width;
		height = that.height;
		dragged= that.dragged;
		canvas = that.canvas;
	}
	return *this;
}

RectangleController::~RectangleController() {}

void RectangleController::leftDown(int x, int y) {
	// MouseListener::leftDown(x,y);
	dragged = true;
	leftX = x;
	topY = y;
}

void RectangleController::leftUp(int x, int y) {
	dragged = false;
	width = x - leftX;
	height = y - topY;

	// rectangle creation goes here..

	if (poly != NULL) {
		poly->drawPersistent(canvas, canvas->pixel_color(255,255,0));
		// canvas->flushPersistent();
	}
}

void RectangleController::movement(int x, int y) {
		// std::cout << "new location (" << x << "," << y << ")" << std::endl;
	if (dragged)
		drawRectangle(leftX, topY, x, y);
	MouseListener::movement(x,y);
	// rectangle construction animation goes here..
}

void RectangleController::drawRectangle(int leftX, int topY, int rightX, int botY) {

	// int xp = 75, yp = 75;
	Point p1 = Point(leftX, topY);
	Point p2 = Point(rightX, topY);
	Point p3 = Point(rightX, botY);
	Point p4 = Point(leftX, botY);
	
	vector <Point> p;
	p.push_back(p1);
	p.push_back(p2);
	p.push_back(p3);
	p.push_back(p4);
	if (poly != NULL)
		delete poly;
	poly = new Polygon(p);
	poly->draw(canvas, canvas->pixel_color(255,255,0));
}