#include "pesawat.h"

Pesawat::Pesawat(Canvas* p_canvas) {
	this->p_canvas = p_canvas;

	setWidth(137);
	setHeight(80);
	
	direction = 2; //ke kiri
	Point P(22,80);
	gun = P;
	// setup the lines
	for (int i = 0; i < 10; ++i) {
		lines.push_back(Line(Point(0, 0), Point(0, 0)));
	}

	lines[0].setPointOne(Point(0,0));
	lines[0].setPointTwo(Point(80,20));

	lines[1].setPointOne(Point(0,20));
	lines[1].setPointTwo(Point(80,0));

	lines[2].setPointOne(Point(40,10));
	lines[2].setPointTwo(Point(40,36));

	lines[3].setPointOne(Point(6,36));
	lines[3].setPointTwo(Point(137,36));

	lines[4].setPointOne(Point(20,60));
	lines[4].setPointTwo(Point(22,80));

	lines[5].setPointOne(Point(6,36));
	lines[5].setPointTwo(Point(6,70));

	lines[6].setPointOne(Point(6,70));
	lines[6].setPointTwo(Point(88,70));

	lines[7].setPointOne(Point(88,49));
	lines[7].setPointTwo(Point(88,70));

	lines[8].setPointOne(Point(137,36));
	lines[8].setPointTwo(Point(137,49));

	lines[9].setPointOne(Point(88,49));
	lines[9].setPointTwo(Point(137,49));
	
	//utk explode
	for (int i=0; i<5; i++) {
		lines.push_back(Line(Point(0,0), Point(0,0)));
	}
	lines[10].setPointOne(Point(45,0));
	lines[10].setPointTwo(Point(0,80));
	
	lines[11].setPointOne(Point(45,0));
	lines[11].setPointTwo(Point(90,80));
	
	lines[12].setPointOne(Point(90,25));
	lines[12].setPointTwo(Point(0,80));
	
	lines[13].setPointOne(Point(90,25));
	lines[13].setPointTwo(Point(0,25));
	
	lines[14].setPointOne(Point(0,25));
	lines[14].setPointTwo(Point(90,80));
}

void Pesawat::draw() {
	for (std::vector<Line>::iterator it = lines.begin(); it != lines.end()-5; it++)
		it->draw(p_canvas, 1, p_canvas->pixel_color(colorRP,colorGP,colorBP));
}

// Override
void Pesawat::setTopLeftPosition(Point p) {
	Point prev = getTopLeftPosition();
	int dx = p.getAbsis()-prev.getAbsis();
	int dy = p.getOrdinat()-prev.getOrdinat();
	Animation::setTopLeftPosition(p);
	for (vector<Line>::iterator it = lines.begin(); it != lines.end(); it++) {
		it->moveRight(dx);
		it->moveDown(dy);
	}
}

void Pesawat::update(double timeElapsed) {
	double distance = speed_x*timeElapsed;
	Point now = getTopLeftPosition();
	
	Point prev = getTopLeftPosition();
	if (prev.getAbsis()==0) 
		direction = 1;
	else if (prev.getAbsis()==p_canvas->get_vinfo().xres-getWidth())
		direction = 2;
		
	if (direction==2)
		now.moveLeft((int) distance);
	else
		now.moveRight((int) distance);
	setTopLeftPosition(now);
}

Point Pesawat::fire() {
	Point now = getTopLeftPosition();
	return Point(now.getAbsis()+gun.getAbsis(), gun.getOrdinat()+11); //10 adalah ukuran projectile
}

void Pesawat::explode(){
	for (std::vector<Line>::iterator it = lines.begin()+10; it != lines.end(); it++)
		it->draw(p_canvas, 1, p_canvas->pixel_color(255,0,0));
}

bool Pesawat::getFlag() {}
