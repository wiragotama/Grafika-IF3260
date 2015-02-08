#include "kapal.h"

Kapal::Kapal(Canvas* p_canvas) {
	this->p_canvas = p_canvas;

	// setup the lines
	for (int i = 0; i < 16; ++i) {
		lines.push_back(Line(Point(0, 0), Point(0, 0)));
	}

	lines[0].setPointOne(Point(0,30));
	lines[0].setPointTwo(Point(0,80));

	lines[1].setPointOne(Point(100,30));
	lines[1].setPointTwo(Point(100,80));

	lines[2].setPointOne(Point(0,30));
	lines[2].setPointTwo(Point(100,30));

	lines[3].setPointOne(Point(0,80));
	lines[3].setPointTwo(Point(100,80));

	lines[4].setPointOne(Point(22,0));
	lines[4].setPointTwo(Point(22,30));

	lines[5].setPointOne(Point(67,0));
	lines[5].setPointTwo(Point(67,30));

	lines[6].setPointOne(Point(22,0));
	lines[6].setPointTwo(Point(67,0));

	lines[7].setPointOne(Point(22,30));
	lines[7].setPointTwo(Point(67,30));

	lines[8].setPointOne(Point(67,2));
	lines[8].setPointTwo(Point(67,12));

	lines[9].setPointOne(Point(77,2));
	lines[9].setPointTwo(Point(77,12));

	lines[10].setPointOne(Point(67,2));
	lines[10].setPointTwo(Point(77,2));

	lines[11].setPointOne(Point(67,12));
	lines[11].setPointTwo(Point(77,12));

	lines[12].setPointOne(Point(91,20));
	lines[12].setPointTwo(Point(91,30));

	lines[13].setPointOne(Point(98,20));
	lines[13].setPointTwo(Point(98,30));

	lines[14].setPointOne(Point(91,20));
	lines[14].setPointTwo(Point(98,20));

	lines[15].setPointOne(Point(91,30));
	lines[15].setPointTwo(Point(98,30));
}

void Kapal::draw() {
	for (std::vector<Line>::iterator it = lines.begin(); it != lines.end(); it++)
		it->drawStraightLine(p_canvas);
}

void Kapal::update(double timeElapsed) {
	double distance = speed_x*timeElapsed;
	Point now = getTopLeftPosition();
	now.moveRight((int) distance);
	setTopLeftPosition(now);
	
	for(int i=0; i<lines.size(); i++){
		lines[i].moveRight((int)distance);
	}
}
