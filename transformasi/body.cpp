#include "body.h"

Body::Body(Canvas *p_canvas, Point topLeftPosition) {
	broken = false;
	
	Point topLeftPosition2(250,50);
	
	Polygon P1(p_canvas, topLeftPosition);
	Polygon P2(p_canvas, topLeftPosition2);
	
	polygons.push_back(P1);
	polygons.push_back(P2);
	
	string ply1 = "body.info";
	polygons[0].loadPolygon(ply1.c_str());
}

Body::~Body() {
}
		
void Body::draw() {
	polygons[0].draw();
	if (broken) {
		polygons[1].draw();
	}
}

void Body::move(int dx, int dy) {
	polygons[0].move(dx, dy);
	polygons[1].move(dx, dy);
}

void Body::broke() {
	broken = true;
	string ply1 = "bodyLeft.info";
	string ply2 = "bodyRight.info";
	polygons[0].erasePoints();
	polygons[1].erasePoints();
	
	polygons[0].loadPolygon(ply1.c_str());
	
	polygons[1].setTopLeftPosition(polygons[0].getTopLeftPosition().getAbsis()+120, polygons[0].getTopLeftPosition().getOrdinat());
	polygons[1].loadPolygon(ply2.c_str());
}

void Body::setTopLeftPosition(Point topLeftPosition) {
	this->topLeftPosition = topLeftPosition;
}

Point Body::getTopLeftPosition() {
	return topLeftPosition;
}
