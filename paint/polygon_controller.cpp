#include "polygon_controller.h"

PolygonController::PolygonController(Canvas* canvas) : MouseListener(canvas) {
	// MouseListener::MouseListener(canvas);
}

PolygonController::PolygonController(const PolygonController& that) : MouseListener (canvas) {
	// this actually don't make sense, but we'll let it slide for now
	point = that.point;
}

PolygonController& PolygonController::operator= (const PolygonController& that) {
	// this actually don't make sense, but we'll let it slide for now
	if (this != &that) {
		point = that.point;
	}
	return *this;
}

PolygonController::~PolygonController() {}

void PolygonController::leftDown(int x, int y) {
	// MouseListener::leftDown(x,y);
	point.push_back(Point(x, y));
}

void PolygonController::leftUp(int x, int y) {}

void PolygonController::rightDown(int x, int y) {
	point.push_back(Point(x, y));
	Polygon poly(point);
	point.clear();
	poly.drawfillPersistent(canvas, canvas->getCurrentColor());
}

void PolygonController::movement(int x, int y) {
		// std::cout << "new location (" << x << "," << y << ")" << std::endl;
	int i;
	for (i = 0; i+1 < point.size(); i++) {
		Line l = Line(point[i], point[i+1]);
		l.draw(canvas, 1, canvas->getCurrentColor());
	}
	if (point.size()) {
		Line l = Line(point[i], Point(x, y));
		l.draw(canvas, 1, canvas->getCurrentColor());
	}

	MouseListener::movement(x,y);
}
