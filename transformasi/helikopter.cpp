#include "helikopter.h"
Helikopter::Helikopter(Canvas *p_canvas, Point topLeftPosition) : body(p_canvas, topLeftPosition), tire(topLeftPosition, 10) {
	this->canvas = p_canvas;
	this->topLeftPosition = topLeftPosition;
	
	Point tmp = topLeftPosition;
	body.setTopLeftPosition(topLeftPosition);
	
	tmp.move(30, body.getHeight()+10);
	tire.setMidPoint(tmp);
}

Helikopter::~Helikopter() {
}

Point Helikopter::getTopLeftPosition() {
	return topLeftPosition;
}

void Helikopter::setTopLeftPosition(Point P) {
	topLeftPosition = P;
}

void Helikopter::move(int dx, int dy) {
	body.move(dx, dy);
	tire.move(dx, dy);
	this->topLeftPosition.move(dx, dy);
	//baling2 move
}

int Helikopter::getWidth() {
	return body.getWidth();
}

int Helikopter::getHeight() {
	return body.getHeight() + tire.getHeight();	
}

void Helikopter::brokeBody() {
	body.broke();
}

void Helikopter::bounceTire() {
	tire.bounce();
}

Tire Helikopter::getTire() {
	return tire;
}

Body Helikopter::getBody() {
	return body;
}

void Helikopter::draw(uint32_t color) {
	body.draw(color);
	tire.draw(canvas, color);
}

bool Helikopter::atBottomOfScreen() {
	return (topLeftPosition.getOrdinat()+body.getHeight()+tire.getHeight() >= canvas->get_vinfo().yres);
}
