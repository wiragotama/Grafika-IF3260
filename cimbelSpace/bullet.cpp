#include "bullet.h"

Bullet::Bullet(int direction, Point topLeftPosition) : line(Point(topLeftPosition.getAbsis()+2,topLeftPosition.getOrdinat()), Point(topLeftPosition.getAbsis()+2,topLeftPosition.getOrdinat()+10)) {
	this-> direction = direction;
	thickness = 4;
	
	setWidth(thickness);
	setHeight(10);
	flag = false; //ni buat resolve masalah segmentation fault pas projectile dah nyampe ujung layar
	
	this->topLeftPosition = topLeftPosition;
}

Bullet::~Bullet() {
}

void Bullet::draw(Canvas *canvas, uint32_t color) {
	if (!flag) {
		line.setPointOne(topLeftPosition);
		Point dua= topLeftPosition;
		dua.setOrdinat(dua.getOrdinat()+getHeight());
		line.setPointTwo(dua);
		line.draw(canvas, thickness, color);
	}
}

void Bullet::update(double timeElapsed, Canvas *p_canvas) {
	double distance = speed_x*timeElapsed;
	Point now = getTopLeftPosition();
	if (direction==1) { //up
		if (now.getOrdinat()<=1) {
			//matikan objek?
			flag = true;
			//delete(this);
		}
		else now.moveUp((int) distance);
	}
	else { //down
		if (now.getOrdinat() >= p_canvas->get_vinfo().yres-getHeight()-1) {
			//matikan objek?
			flag = true;
			//delete this;
		}
		else now.moveDown((int) distance);
	}
	
	setTopLeftPosition(now);
	
	float temp;
	if (direction==1) temp = 1.0 + 1.0/60.0 * now.getOrdinat() * 5.0;
	else if (direction==2) temp = 1.0 + (3840.0/now.getOrdinat()) / 3.0;
	if (temp > 10)
		thickness = 5;
	else 
		thickness = (int)temp;
		
}

void Bullet::checkFlag() {
	if (direction<=1) { //up
		if (topLeftPosition.getOrdinat()<= 1) {
			//matikan objek?
			flag = true;
			//delete(this);
		}
	}
	else { //down
		if (topLeftPosition.getOrdinat() >= 640-getHeight()-1) {
			//matikan objek?
			flag = true;
			//delete this;
		}
	}
}

void Bullet::move(int dx, int dy) {
	topLeftPosition.move(dx, dy);
	line.move(dx, dy);
	checkFlag();
}

void Bullet::setTopLeftPosition(Point p) {
	topLeftPosition = p;
}

void Bullet::explode() {}

bool Bullet::getFlag() {
	return flag;
}

Point Bullet::getTopLeftPosition() {
	return topLeftPosition;
}

void Bullet::setWidth(int width) {
	this->width = width;
}

void Bullet::setHeight(int height) {
	this->height = height;
}

int Bullet::getWidth() {
	return width;
}

int Bullet::getHeight() {
	return height;
}
