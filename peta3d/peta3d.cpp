#include "peta3d.h"

Peta3D::Peta3D() {
	this->loadPeta2d("pulau/jawa.info");
	this->loadPeta2d("pulau/kalimantan.info");
	this->loadPeta2d("pulau/papua.info");
	this->loadPeta2d("pulau/sulawesi.info");
	this->loadPeta2d("pulau/sumatera.info");
	
	generetePeta3dSurfaces();
	generetePeta3dFromSurface();
	
	relativePositionX = 0;
	relativePositionY = 0;
}

void Peta3D::drawPeta(Canvas* canvas) {
	for(vector<Polygon>::iterator it = petaSurface.begin(); it != petaSurface.end(); ++it) {
		it->drawBackground(canvas, canvas->pixel_color(255,0,0));
	}
}

void Peta3D::drawPeta3d(Canvas* canvas){
	for(vector<Line>::iterator it = peta3d.begin(); it != peta3d.end(); ++it) {
		it->draw(canvas, 1, canvas->pixel_color(255,255,255));
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
		Polygon temp(Point(0,0));
		temp.addPoint(upperPoints[i]);
		temp.addPoint(bottomPoints[i]);
		temp.addPoint(bottomPoints[i-1]);
		temp.addPoint(upperPoints[i-1]);
		retPol.push_back(temp);
	}
	Polygon temp(Point(0,0));
	temp.addPoint(upperPoints[0]);
	temp.addPoint(bottomPoints[0]);
	temp.addPoint(bottomPoints[bottomPoints.size()-1]);
	temp.addPoint(upperPoints[bottomPoints.size()-1]);
	retPol.push_back(temp);
		
	//sort polygon
	sort(retPol.begin(), retPol.end(), Polygon::sortTopLeft);
	retPol.push_back(*polygon);	
	
	return retPol;
}

void Peta3D::generetePeta3dSurfaces(){
	for(int i=0; i<peta2d.size(); i++) {
		vector<Polygon> surfaceFromOnePolygon = polygonTo3D(&(peta2d[i]), 10);
		petaSurface.insert(petaSurface.end(), surfaceFromOnePolygon.begin(), surfaceFromOnePolygon.end());
	}
}

void Peta3D::generetePeta3dFromSurface(){
	for(int i=0; i<petaSurface.size(); i++){
		vector<Line> hiddenLineRemoved;
		vector<Point> poly = petaSurface[i].getPoints();
		if(poly.size()>0)
			poly.push_back(poly[0]);
				
		//Untuk setiap garis yang telah ada, cek hiddenLineRemoval dengan surface baru
		for(int j=0; j<peta3d.size(); j++){
			vector<Point> daftar;
			
			daftar.push_back(peta3d[j].getPointOne());
			daftar.push_back(peta3d[j].getPointTwo());
			
			//Cek perpotongan garis dengan setiap sisi poligon
			for(int k=0; k<poly.size()-1; k++) {
				if((Point::orientation(peta3d[j].getPointOne(), peta3d[j].getPointTwo(), poly[k]) < 2 && Point::orientation(peta3d[j].getPointOne(), peta3d[j].getPointTwo(), poly[k+1]) == 2) ||
				   (Point::orientation(peta3d[j].getPointOne(), peta3d[j].getPointTwo(), poly[k]) == 2 && Point::orientation(peta3d[j].getPointOne(), peta3d[j].getPointTwo(), poly[k+1]) < 2)){
					Line ltemp(poly[k], poly[k+1]);
					Point* p;
					p=NULL;
					p = peta3d[j].getIntersectionPointWith(ltemp);

					if (p!=NULL) {
						daftar.push_back(*p);
						free(p);
					}
				}
			}
			
			sort(daftar.begin(), daftar.end(), Point::pointGreaterThan);
			
			for(int k=0; k+1<daftar.size(); k++){
				int midX = (daftar[k].getAbsis()+ daftar[k+1].getAbsis())/2;
				int midY = (daftar[k].getOrdinat()+ daftar[k+1].getOrdinat())/2;
				
				
				Point midPoint = Point(midX , midY);
				if(!petaSurface[i].isPointInside(midPoint)) {
					hiddenLineRemoved.push_back(Line(daftar[k], daftar[k+1]));
				} 

			}
			
		}
		
		peta3d = hiddenLineRemoved;
		vector<Line> newLines = petaSurface[i].getLines();
		peta3d.insert(peta3d.end(), newLines.begin(), newLines.end());
	}
}

void Peta3D::move(int dx, int dy){
	if(abs(relativePositionX+dx) <100 && abs(relativePositionY+dy) <100){
		relativePositionX += dx;
		relativePositionY += dy;
		for(int i=0; i<peta3d.size(); i++){
			peta3d[i].move(dx, dy);
		}
	}
}
