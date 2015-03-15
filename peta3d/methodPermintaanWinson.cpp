#include "../core/canvas.h"
#include "../core/header.h"
#include "../core/line.h"
#include "../pattern/polygon.h"
#include "../pattern/pattern.h"
#include <vector>
#include <algorithm>

vector<Polygon> polygonTo3D(Polygon* polygon, int dy) {
	vector<Point> bottomPoints = polygon->getPoints();
	vector<Point> upperPoints = polygon->getPoints();
	
	for (int i=0; i<bottomPoints.size(); i++) {
		bottomPoints[i].move(0, dy);
	}
	
	vector<Polygon> retPol;
	for (int i=1; i<bottomPoints.size(); i++) {
		Polygon temp;
		temp.addPoint(upperPoints[i]);
		temp.addPoint(bottomPoints[i]);
		temp.addPoint(bottomPoints[i-1]);
		temp.addPoint(upperPoints[i-1]);
		Point TLP(temp.getMostLeftPoint().getAbsis(), temp.getMostUpperPoint().getOrdinat());
		temp.setTopLeftPosition(TLP);
		retPol.push_back(temp);
	}
	Polygon temp;
	temp.addPoint(upperPoints[0]);
	temp.addPoint(bottomPoints[0]);
	temp.addPoint(bottomPoints[bottomPoints.size()-1]);
	temp.addPoint(upperPoints[bottomPoints.size()-1]);
	Point TLP(temp.getMostLeftPoint().getAbsis(), temp.getMostUpperPoint().getOrdinat());
	temp.setTopLeftPosition(TLP);
	retPol.push_back(temp);
		
	//sort polygon
	sort(retPol.begin(), retPol.end(), Polygon::sortTopLeft);
	retPol.push_back(*polygon);	
	
	return retPol;
}

int main() {
	Canvas canvas;
	Polygon polygon(Point(0,0));
	string ptr = "polygon.info";
	polygon.loadPolygon(ptr.c_str());
	vector<Polygon> dummy = polygonTo3D(&polygon, 5);
	for (int i=0; i<dummy.size(); i++) {
		dummy[i].setFirePoint(dummy[i].getSuitableFirePoint(&canvas));
		dummy[i].printInfo();
		printf("\n");
	}
	return 0;
}
