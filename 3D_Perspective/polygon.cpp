#include "polygon.h"

Polygon::Polygon(vector<Point> nodes){
	this->nodes = nodes;
}

vector<Point> Polygon::getPoints() const{
	return nodes;
}

vector<Line> Polygon::getLines() const {
	vector<Point> tempPoints = getPoints();
	vector<Line> polygonLines;
	if(tempPoints.size()>0)
		tempPoints.push_back(tempPoints[0]);
	for(int i=0; i<(int)tempPoints.size()-1; i++){
		polygonLines.push_back( Line(tempPoints[i], tempPoints[i+1]) );
	}
	return polygonLines;
}

void Polygon::draw(Canvas *canvas, uint32_t color){
	vector<Line> lines = getLines();
	for(int i=0; i<(int)lines.size(); i++){
		lines[i].draw(canvas, 1, color);
	}
}
