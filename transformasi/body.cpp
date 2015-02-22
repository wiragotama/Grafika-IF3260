#include "body.h"

Body::Body(Canvas *p_canvas) {
	broken = false;
	
	Point topLeftPosition1(100,50);
	Point topLeftPosition2(250,50);
	
	Polygon P1(p_canvas, topLeftPosition1);
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
}
