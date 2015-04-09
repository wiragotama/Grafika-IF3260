#include "mouse_listener.h"

MouseListener::MouseListener(Canvas *canvas) {
	this->canvas = canvas;
}
MouseListener::MouseListener(const MouseListener&) {}
MouseListener& MouseListener::operator= (const MouseListener&) {}
MouseListener::~MouseListener() {}

void MouseListener::leftDown(int, int) {}
void MouseListener::leftUp(int x, int y) {
}
void MouseListener::rightDown(int, int) {}
void MouseListener::rightUp(int, int) {}
void MouseListener::middleDown(int, int) {}
void MouseListener::middleUp(int, int) {}
void MouseListener::movement(int x, int y) {
	//draw mouse
	Line l = Line(Point(x,y), Point(x+5,y+5));
	l.draw(canvas,2,canvas->pixel_color(255,255,255));

	int xp = 75, yp = 75;
	Point p1 = Point(xp-5, yp-5);
	Point p2 = Point(xp+5, yp-5);
	Point p3 = Point(xp+5, yp+5);
	Point p4 = Point(xp-5, yp+5);
	vector <Point> p;
	p.push_back(p1);
	p.push_back(p2);
	p.push_back(p3);
	p.push_back(p4);
	Polygon poly = Polygon(p);
	poly.draw(canvas, canvas->pixel_color(255,255,0));

	canvas->flush();
}
