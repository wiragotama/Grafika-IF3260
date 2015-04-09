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

void Polygon::drawfill(Canvas *canvas, uint32_t color){
	const double EPSILON = 1e-3;
	vector<Line> lines = getLines();
	double slope[lines.size()];
	
	for(int i=0; i<lines.size(); i++)
	{
		Point p1 = lines[i].getPointOne();
		Point p2 = lines[i].getPointTwo();
		
		double dy = p2.getOrdinat() - p1.getOrdinat();
		double dx = p2.getAbsis() - p1.getAbsis();

		if(fabs(dy) < EPSILON) slope[i]=1.0;
		else if(fabs(dx) < EPSILON) slope[i]=0.0;
		else slope[i] = dx/dy;
	}
	
	int minY = floor( getMinY() );
	int maxY = ceil( getMaxY() );
	for(int y=minY; y<=maxY; y++){
		
		vector<int> intersect;
		for(int i=0; i<lines.size(); i++){
			Point p1 = lines[i].getPointOne();
			Point p2 = lines[i].getPointTwo();
			if( ((round(p1.getOrdinat())<=y)&&(round(p2.getOrdinat())>y)) || 
				((round(p1.getOrdinat())>y)&&(round(p2.getOrdinat())<=y)) ){
				intersect.push_back( round(p1.getAbsis()+slope[i]*(y-p1.getOrdinat())) );
			}
		}
		
		sort(intersect.begin(), intersect.end());
		
		for(int i=0; i+1<intersect.size(); i+=2){
			Line line( Point(intersect[i],y) , Point(intersect[i+1],y));
			line.draw(canvas, 1, color);
		}
	}
}

double Polygon::getMinX(){
	double most;
	most = nodes[0].getAbsis();
	for(int i=1; i<nodes.size(); i++){
		if(nodes[i].getAbsis() < most) most = nodes[i].getAbsis();
	}
	return most;
}

double Polygon::getMaxX(){
	double most;
	most = nodes[0].getAbsis();
	for(int i=1; i<nodes.size(); i++){
		if(nodes[i].getAbsis() > most) most = nodes[i].getAbsis();
	}
	return most;
}

double Polygon::getMinY(){
	double most;
	most = nodes[0].getOrdinat();
	for(int i=1; i<nodes.size(); i++){
		if(nodes[i].getOrdinat() < most) most = nodes[i].getOrdinat();
	}
	return most;
}

double Polygon::getMaxY(){
	double most;
	most = nodes[0].getOrdinat();
	for(int i=1; i<nodes.size(); i++){
		if(nodes[i].getOrdinat() > most) most = nodes[i].getOrdinat();
	}
	return most;
}
