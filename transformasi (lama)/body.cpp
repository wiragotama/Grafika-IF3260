#include "body.h"

Body::Body(Canvas *p_canvas, Point topLeftPosition) {
	broken = false;
	
	Polygon P1(p_canvas, topLeftPosition);
	Polygon P2(p_canvas, topLeftPosition);
	
	polygons.push_back(P1);
	polygons.push_back(P2);
	
	string ply1 = "body.info";
	polygons[0].loadPolygon(ply1.c_str());
}

Body::~Body() {
}
		
void Body::draw(uint32_t color) {
	polygons[0].draw(color);
	if (broken) {
		polygons[1].draw(color);
	}
}

void Body::move(int dx, int dy)  {
	polygons[0].move(dx, dy);
	if (broken)
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

int Body::getWidth() {
	if (broken)
		return polygons[1].getMostRightPoint().getAbsis() - polygons[0].getMostLeftPoint().getAbsis();
	else
		return polygons[0].getMostRightPoint().getAbsis() - polygons[0].getMostLeftPoint().getAbsis();
}

int Body::getHeight() {
	return polygons[0].getMostBottomPoint().getOrdinat() - polygons[0].getMostUpperPoint().getOrdinat();
}
