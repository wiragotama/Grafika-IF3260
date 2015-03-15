#include "peta3d.h"

Peta3D::Peta3D() {
	this->loadPeta2d("pulau/jawa.info");
	this->loadPeta2d("pulau/kalimantan.info");
	this->loadPeta2d("pulau/papua.info");
	this->loadPeta2d("pulau/sulawesi.info");
	this->loadPeta2d("pulau/sumatera.info");
}

void Peta3D::drawPeta(Canvas* canvas) {
	for(vector<Polygon>::iterator it = peta2d.begin(); it != peta2d.end(); ++it) {
		it->drawBackground(canvas, canvas->pixel_color(255,0,0));
	}
}

void Peta3D::loadPeta2d(const char* filename) {
	int count, p1, p2;
	uint32_t value;
	FILE *file;
	file = fopen(filename,"r");
	fscanf(file, "%d", &count);
	Polygon polygon(Point(0,0));

	for(int it=0; it<count ; ++it) {
		fscanf(file, "%d %d", &p1, &p2);
		Point p(p1,p2);
		polygon.addPoint(p);
	}
	peta2d.push_back(polygon);
	fclose(file);
}

vector<Polygon> Peta3D::polygonTo3D(Polygon* polygon, int dy) {
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

void Peta3D::generetePeta3dSurfaces(){
	for(int i=0; i<peta2d.size(); i++) {
		//vector<Polygon> surfaceFromOnePolygon = polygonTo3D(&peta2d[i], 10);
		//peta3d.insert(peta3d.begin(), surfaceFromOnePolygon.begin(), surfaceFromOnePolygon.end());
	}
}
