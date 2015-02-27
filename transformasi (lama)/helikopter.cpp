#include "helikopter.h"

Helikopter::Helikopter(Canvas *p_canvas, Point topLeftPosition) : kincir(p_canvas), body(p_canvas, topLeftPosition), tire(topLeftPosition, 10) {
	this->canvas = p_canvas;
	this->topLeftPosition = topLeftPosition;
	
	Point tmp = topLeftPosition;
	body.setTopLeftPosition(topLeftPosition);
	
	tmp.move(30, body.getHeight()+10);
	tire.setMidPoint(tmp);
	
	kincir.move(-180, -350);
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
	kincir.move(dx, dy);
}

int Helikopter::getWidth() {
	return body.getWidth();
}

int Helikopter::getHeight() {
	return body.getHeight() + tire.getHeight();	
}

void Helikopter::brokeBody() {
	body.broke();
	kincir.move(-40, -100);
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
	kincir.draw();
	double thirtyDegree = 0.03490658503989;
	kincir.rotate(thirtyDegree);
}

void Helikopter::kincirDestroy() {
	kincir.destroy();
}

bool Helikopter::atBottomOfScreen() {
	return (topLeftPosition.getOrdinat()+body.getHeight()+tire.getHeight() >= canvas->get_vinfo().yres);
}
