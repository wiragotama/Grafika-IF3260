#include "mouse_listener.h"

MouseListener::MouseListener(Canvas *canvas) {
	this->canvas = canvas;
}
MouseListener::MouseListener(const MouseListener&) {}
MouseListener& MouseListener::operator= (const MouseListener&) {}
MouseListener::~MouseListener() {}

void MouseListener::leftDown(int, int) {}
void MouseListener::leftUp(int, int) {}
void MouseListener::rightDown(int, int) {}
void MouseListener::rightUp(int, int) {}
void MouseListener::middleDown(int, int) {}
void MouseListener::middleUp(int, int) {}
void MouseListener::movement(int x, int y) {
	Line l = Line(Point(x,y), Point(x+5,y+5));
	l.draw(canvas,2,canvas->pixel_color(255,255,255));
	// canvas->putPixelColor(x, y, canvas->pixel_color(255,0,0));
	canvas->flush();
}
