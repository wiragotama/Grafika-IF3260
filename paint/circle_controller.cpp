#include "circle_controller.h"

CircleController::CircleController(Canvas* canvas) : MouseListener(canvas) {
	// MouseListener::MouseListener(canvas);
	dragged = false;
	poly = NULL;
}

CircleController::CircleController(const CircleController& that) : MouseListener (canvas) {
	// this actually don't make sense, but we'll let it slide for now
	dragged= that.dragged;
	canvas = that.canvas;
}

CircleController& CircleController::operator= (const CircleController& that) {
	// this actually don't make sense, but we'll let it slide for now
	if (this != &that) {
		dragged= that.dragged;
		canvas = that.canvas;
	}
	return *this;
}

CircleController::~CircleController() {}

void CircleController::leftDown(int x, int y) {
	// MouseListener::leftDown(x,y);
	center = Point(x,y);
	dragged = true;
}

void CircleController::leftUp(int x, int y) {
	dragged = false;
	int deltaX = x - center.getAbsis();
	int deltaY = y - center.getOrdinat();
	double length = sqrt(deltaX*deltaX + deltaY *deltaY) ;
	Circle c = Circle(center.getAbsis(), center.getOrdinat(), length);
	c.drawfillPersistent(canvas, canvas->pixel_color(255,255,0));

}

void CircleController::movement(int x, int y) {
	if (dragged) {
		int deltaX = x - center.getAbsis();
		int deltaY = y - center.getOrdinat();
		double length = sqrt(deltaX*deltaX + deltaY *deltaY) ;
		drawCircle(length);
	}
	MouseListener::movement(x,y);
	// rectangle construction animation goes here..
}

void CircleController::drawCircle(int r) {
	Circle c = Circle(center.getAbsis(), center.getOrdinat(), r);
	c.drawfill(canvas, canvas->pixel_color(255,255,0));
	// // int xp = 75, yp = 75;
	// Point p1 = Point(leftX, topY);
	// Point p2 = Point(rightX, topY);
	// Point p3 = Point(rightX, botY);
	// Point p4 = Point(leftX, botY);
	
	// vector <Point> p;
	// p.push_back(p1);
	// p.push_back(p2);
	// p.push_back(p3);
	// p.push_back(p4);
	// if (poly != NULL)
	// 	delete poly;
	// poly = new Polygon(p);
	// poly->draw(canvas, canvas->pixel_color(255,255,0));
}