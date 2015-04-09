#include "polygon.h"
#include "canvas.h"
#include "point.h"
#include "circle.h"
#include <vector>

using namespace std;


int main(){
	Canvas canvas;
	
	vector<Point> nodes;
	nodes.push_back( Point(50,50) );
	nodes.push_back( Point(100,50) );
	nodes.push_back( Point(70,80) );
	nodes.push_back( Point(40,90) );
	nodes.push_back( Point(60,70) );
	
	Polygon poly(nodes);
	poly.drawfill(&canvas, 255);
	poly.draw(&canvas, 255<<8);
	
	Circle circle(300,300,100);
	circle.drawfill(&canvas, 255);
	
	canvas.flush();
	return 0;
}
