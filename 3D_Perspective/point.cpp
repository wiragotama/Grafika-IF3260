#include "point.h"

Point::Point(){
	setAbsis(0);
	setOrdinat(0);
}

Point::Point(double new_x, double new_y){
	setAbsis(new_x);
	setOrdinat(new_y);
}

double Point::getAbsis() const{
	return x;
}

double Point::getOrdinat() const{
	return y;
}

void Point::setAbsis(double x){
	this->x = x;
}

void Point::setOrdinat(double y){
	this->y = y;
}

bool Point::operator==(const Point p) const{
	return (getAbsis() == p.getAbsis()) && (getOrdinat() == p.getOrdinat());
}

void Point::draw(Canvas *canvas, uint32_t color) {
	canvas->putPixelColor(getAbsis(), getOrdinat(), color);
}

void Point::drawPersistent(Canvas *canvas, uint32_t color) {
	canvas->putPixelColorPersistent(getAbsis(), getOrdinat(), color);
}
