#include "triangle_controller.h"

TriangleController::TriangleController(Canvas* canvas) : MouseListener(canvas) {
	// MouseListener::MouseListener(canvas);
	state = 0;
	poly = NULL;
}

TriangleController::TriangleController(const TriangleController& that) : MouseListener (canvas) {
	// this actually don't make sense, but we'll let it slide for now
	state = that.state;
	point[0] = that.point[0];
	point[1] = that.point[1];
	point[2] = that.point[2];
}

TriangleController& TriangleController::operator= (const TriangleController& that) {
	// this actually don't make sense, but we'll let it slide for now
	if (this != &that) {
		state = that.state;
		point[0] = that.point[0];
		point[1] = that.point[1];
		point[2] = that.point[2];
	}
	return *this;
}

TriangleController::~TriangleController() {}

void TriangleController::leftDown(int x, int y) {
	// MouseListener::leftDown(x,y);
	point[state] = Point(x,y);
}

void TriangleController::leftUp(int x, int y) {
	state++;
	// rectangle creation goes here..

	if (poly != NULL) {
		poly->drawPersistent(canvas, canvas->pixel_color(255,255,0));
		// canvas->flushPersistent();
	}
}

void TriangleController::movement(int x, int y) {
		// std::cout << "new location (" << x << "," << y << ")" << std::endl;
	if (state == 1) {
		Line l = Line(point[0], Point(x,y));
		l.draw(canvas,1,canvas->pixel_color(255,255,0));
	} else if (state == 2) {
		Line l = Line(point[0], point[1]);
		l.draw(canvas,1,canvas->pixel_color(255,255,0));
		Line l1 = Line(point[1], Point(x,y));
		l1.draw(canvas,1,canvas->pixel_color(255,255,0));
	} else if (state == 3) {
		drawTriangle();
		state = 0;
	}

	MouseListener::movement(x,y);
}

void TriangleController::drawTriangle() {	
	vector <Point> p;
	p.push_back(point[0]);
	p.push_back(point[1]);
	p.push_back(point[2]);
	// p.push_back(p4);
	if (poly != NULL)
		delete poly;
	poly = new Polygon(p);
	poly->drawPersistent(canvas, canvas->pixel_color(255,255,0));
}