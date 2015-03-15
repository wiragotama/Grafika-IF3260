#include "helikopter.h"

Helikopter::Helikopter(Point topLeftPosition) : kincir(topLeftPosition), body(topLeftPosition), tire(topLeftPosition, 3) {
	this->topLeftPosition = topLeftPosition;
	
	Point tmp = topLeftPosition;
	body.setTopLeftPosition(topLeftPosition);
	
	tmp.move(15, body.getHeight());
	tire.setMidPoint(tmp);
	
	kincir.move(body.getWidth()/2,body.getHeight()/2);
}

Helikopter::~Helikopter() {
}

vector<Polygon> Helikopter::getAllPolygons() const {
    vector<Polygon> result = body.getPolygons();
    vector<Polygon> result2 = kincir.getPolygons();
    result.insert(result.end(), result2.begin(), result2.end());
    return result;
}

Point Helikopter::getTopLeftPosition() {
	return topLeftPosition;
}

void Helikopter::setTopLeftPosition(Point P) {
	topLeftPosition = P;
}

void Helikopter::move(int dx, int dy) {
	if ((body.getBrokenFlag()==true) && (getTopLeftPosition().getOrdinat()%5==0)) 
		body.separateBrokenParts(2, 0);
	body.move(dx, dy);
	tire.move(dx, dy);
	this->topLeftPosition.move(dx, dy);
	kincir.move(dx, dy);
}

void Helikopter::setColor(uint32_t color) {
	this->color = color;
}

uint32_t Helikopter::getColor() {
	return color;
}

int Helikopter::getWidth() {
	return body.getWidth();
}

int Helikopter::getHeight() {
	return body.getHeight() + tire.getHeight();	
}

void Helikopter::brokeBody() {
	body.broke();
	kincir.move(0, -100);
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

void Helikopter::draw(Canvas *canvas, uint32_t color) {
	body.draw(canvas, color);
	tire.draw(canvas, color);
	kincir.draw(canvas, color);
	double thirtyDegree = 0.03490658503989;
	kincir.rotate(thirtyDegree);
}

void Helikopter::kincirDestroy() {
	kincir.destroy();
}

bool Helikopter::atBottomOfScreen(int yres) {
	return (topLeftPosition.getOrdinat()+body.getHeight()+tire.getHeight() >= yres);
}
