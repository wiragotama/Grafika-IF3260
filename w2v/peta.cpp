#include "peta.h"

Peta::Peta() {
	this->loadFile("pulau/jawa.info");
	this->loadFile("pulau/kalimantan.info");
	this->loadFile("pulau/papua.info");
	this->loadFile("pulau/sulawesi.info");
	this->loadFile("pulau/sumatera.info");
}

Peta::~Peta() {}

void Peta::windowToView(Canvas *canvas) {
	for(vector<Polygon>::iterator it = islands.begin(); it != islands.end(); ++it) {
		it->draw(canvas, canvas->pixel_color(255,0,0));
	}
}

void Peta::show_s_view_frame(Canvas *canvas){
	Point p1(500,350);
	Point p2(600,350);
	Point p3(600,450);
	Point p4(500,450);
	s_view_frame.addPoint(p1);
	s_view_frame.addPoint(p2);
	s_view_frame.addPoint(p3);
	s_view_frame.addPoint(p4);
	s_view_frame.draw(canvas, canvas->pixel_color(0,255,0));
}	

void Peta::loadFile(const char *filename) {
	int count, p1, p2;
	uint32_t value;
	FILE *file;
	file = fopen(filename,"r");
	fscanf(file, "%d", &count);
	Polygon polygon;

	for(int it=0; it<count ; ++it) {
		fscanf(file, "%d %d", &p1, &p2);
		Point p(p1,p2);
		polygon.addPoint(p);
	}
	islands.push_back(polygon);
	fclose(file);
}
