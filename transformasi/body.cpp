#include "body.h"

Body::Body (Canvas *p_canvas) {
	broken = false;
	topLeftPosition = Point(0,0);
}

Body::~Body() {
}

void Body::draw() {
	polygons[0].draw();
	if (broken) 
		polygons[1].draw();
}

void Body::move(int dx, int dy) {
	polygons[0].move(dx,dy);
	if(broken)
		polygons[1].move(dx,dy);
}

void Body::setTopLeftPosition(Point p) {
	polygons[0].setTopLeftPosition(p.getAbsis(),p.getOrdinat());
	if(broken)
		polygons[1].setTopLeftPosition(p.getAbsis()+250,p.getOrdinat());
}

void Body::broke(const char* filename1, const char* filename2, const char* pattern) {
	broken = true;
	polygons[0].loadPolygon(filename1);
	polygons[0].loadPattern(pattern);
	polygons[1].loadPolygon(filename2);
	polygons[1].loadPattern(pattern);
}
