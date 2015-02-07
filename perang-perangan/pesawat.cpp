#include "pesawat.h"

Pesawat::Pesawat(Canvas* p_canvas) {
	this->p_canvas = p_canvas;

	setWidth(137);
	setHeight(80);

	// setup the lines
	for (int i = 0; i < 16; ++i) {
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
}

void Pesawat::draw() {
	for (std::vector<Line>::iterator it = lines.begin(); it != lines.end(); it++)
		it->drawStraightLine(p_canvas);
}

// Override
void Pesawat::setTopLeftPosition(Point p) {
	Point prev = getTopLeftPosition();
	int dx = p.getAbsis()-prev.getAbsis();
	int dy = p.getOrdinat()-prev.getOrdinat();
	Animation::setTopLeftPosition(p);
	for (vector<Line>::iterator it = lines.begin(); it != lines.end(); it++) {
		it->eraseStraightLine(p_canvas);
		it->moveRightDown(dx, dy);
	}
}

void Pesawat::update(double timeElapsed) {
	double distance = speed_x*timeElapsed;
	Point now = getTopLeftPosition();
	now.moveLeft((int) distance);
	setTopLeftPosition(now);
}
