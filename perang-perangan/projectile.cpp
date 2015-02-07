#include "projectile.h"

Projectile::Projectile(Canvas *canvas, int direction) : line(Point(0,0), Point(0,10)) {
	this->p_canvas = canvas;
	this-> direction = direction;
	thickness = 10;
	
	setWidth(1);
	setHeight(10);
	
	flag = false; //ni buat resolve masalah segmentation fault pas projectile dah nyampe ujung layar
}

Projectile::~Projectile() {
}

void Projectile::draw() {
	if (!flag) {
		line.setPointOne(getTopLeftPosition());
		Point dua= getTopLeftPosition();
		dua.setOrdinat(dua.getOrdinat()+10);
		line.setPointTwo(dua);
		line.drawThickLine(p_canvas, thickness, p_canvas->pixel_color(projectileR,projectileG,projectileB));
	}
}

void Projectile::update(double timeElapsed) {
	double distance = speed_x*timeElapsed;
	Point now = getTopLeftPosition();
	if (direction==1) { //up
		if (now.getOrdinat()==0) {
			//matikan objek?
			flag = true;
			//delete(this);
		}
		else now.moveUp((int) distance);
	}
	else { //down
		if (now.getOrdinat() == p_canvas->get_vinfo().yres-getHeight()-1) {
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
		thickness = 10.0;
	else 
		thickness = temp;
		
}

void Projectile::setTopLeftPosition(Point p) {
	Animation::setTopLeftPosition(p);
	line.eraseThickLine(p_canvas, thickness);
}

void Projectile::explode() {}

bool Projectile::getFlag() {
	return flag;
}
