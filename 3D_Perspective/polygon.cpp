#include "polygon.h"

Polygon::Polygon(vector<Point> nodes){
	color = NULL;
	this->nodes = nodes;
}

Polygon::~Polygon(){
	if(color != NULL)
		delete color;
}

Polygon::Polygon(const Polygon& poly){
	nodes = poly.nodes;
	*color = *(poly.color);
}

Polygon& Polygon::operator=(const Polygon& ply){
	nodes = ply.nodes;
	*color = *(ply.color);
	return *this;
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
