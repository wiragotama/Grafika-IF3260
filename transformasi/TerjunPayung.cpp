#include "TerjunPayung.h"

TerjunPayung::TerjunPayung (Canvas *canvas, vector<Point> points, Point topLeftPosition) {
	this->canvas = canvas;
	this->points = points;
	this->topLeftPosition = topLeftPosition;
}

TerjunPayung::~TerjunPayung() {

}

void TerjunPayung::move(int dx, int dy) {

}

void TerjunPayung::draw() {
	for (int i=1; i<points.size(); i++) {
		Line line(points[i], points[i-1]);
		line.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
		line.draw(canvas, 1.0, canvas->pixel_color(255,0,0));
	}
	Line line(points[points.size()-1], points[0]);
	line.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
	line.draw(canvas, 1.0, canvas->pixel_color(255,0,0));
	canvas->flush();
}
