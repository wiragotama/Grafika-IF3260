#include "TerjunPayung.h"

TerjunPayung::TerjunPayung (Canvas *canvas, Point topLeftPosition) : parachute(Point(100,100),50), head(Point(100,80), 10){
	this->canvas = canvas;
	this->topLeftPosition = topLeftPosition;
	for (int i = 0; i < 4; ++i) {
		this->lines.push_back(Line(Point(0, 0), Point(0, 0)));
	}
	this->lines[0].setPointOne(Point(50,100));
	this->lines[0].setPointTwo(Point(150,100));

	this->lines[1].setPointOne(Point(100,90));
	this->lines[1].setPointTwo(Point(100,150));

	this->lines[2].setPointOne(Point(100,150));
	this->lines[2].setPointTwo(Point(80,170));

	this->lines[3].setPointOne(Point(100,150));
	this->lines[3].setPointTwo(Point(120,170));

}

TerjunPayung::~TerjunPayung() {

}

void TerjunPayung::moveDown(int d) {
	for (vector<Line>::iterator it = lines.begin(); it != lines.end(); it++) {
		it->moveDown(d);
	}
	this->head.moveDown(d);
	this->parachute.moveDown(d);
}
	
void TerjunPayung::draw() {
	vector <Line> lines_cpy = lines;
	for (vector<Line>::iterator it = lines_cpy.begin(); it != lines_cpy.end(); it++) {
		it->move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
		it->draw(canvas, 1, canvas->pixel_color(255,0,0));
	}

	Circle head_cpy = head, parachute_cpy = parachute;
	head_cpy.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
	head_cpy.drawFull(canvas, canvas->pixel_color(255,0,0));
	parachute_cpy.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
	parachute_cpy.drawSemiTop(canvas, canvas->pixel_color(255,0,0));
	canvas->flush();
}