#include "line.h"

//vector initiation
int dash[2] = {4,2};
vector<int> ve(1,1);
vector<int> dl(dash, dash+sizeof(dash)/sizeof(dash[0]));

//patternList member initialization
Pattern straight_line = { .body = ve, .thickness = ve};
Pattern dashed_line = { .body = dl, .thickness = ve};

//static const member initialization
Pattern pat[] = {straight_line, dashed_line};
const vector<Pattern> Line::patternList(pat, pat+sizeof(pat) / sizeof(pat[0]));

/*************************/
/* Method implementation */
/*************************/
Line::Line(Point P1, Point P2) {
	this->point[0] = P1;
	this->point[1] = P2;
}

Line::~Line() {}

Point Line::getPointOne() {
	return point[0];
}

Point Line::getPointTwo() {
	return point[1];
}

void Line::setPointOne(Point P) {
	this->point[0] = P;
}

void Line::setPointTwo(Point P) {
	this->point[1] = P;
}

void Line::drawThickLine(Canvas *canvas, float thickness, uint32_t color) {
	int x1 = point[1].getAbsis();
	int x0 = point[0].getAbsis();

	int y1 = point[1].getOrdinat();
	int y0 = point[0].getOrdinat();

	int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2; /* error value e_xy */

	for(;;) {  /* loop */
		for(int i=y0-thickness+1; i<=y0+thickness-1; i++)
			for(int j=x0-thickness+1; j<=x0+thickness-1; j++)
				canvas->putPixelColor(j, i, color);
		
		if (x0==x1 && y0==y1) break;
			e2 = 2*err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

void Line::drawStraightLine(Canvas *canvas, uint32_t color) {
	int x1 = point[1].getAbsis();
	int x0 = point[0].getAbsis();

	int y1 = point[1].getOrdinat();
	int y0 = point[0].getOrdinat();

	int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2; /* error value e_xy */

	for(;;) {  /* loop */
		canvas->putPixelColor(x0, y0, color);
		if (x0==x1 && y0==y1) break;
			e2 = 2*err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

void Line::eraseStraightLine(Canvas *canvas) {
	int x1 = point[1].getAbsis();
	int x0 = point[0].getAbsis();

	int y1 = point[1].getOrdinat();
	int y0 = point[0].getOrdinat();

	int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2; /* error value e_xy */

	for(;;) {  /* loop */
		canvas->putPixelRGB(x0, y0, 0, 0, 0);
		if (x0==x1 && y0==y1) break;
			e2 = 2*err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

void Line::eraseThickLine(Canvas *canvas, float thickness) {
	int x1 = point[1].getAbsis();
	int x0 = point[0].getAbsis();

	int y1 = point[1].getOrdinat();
	int y0 = point[0].getOrdinat();

	int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2; /* error value e_xy */

	for(;;) {  /* loop */
		for(int i=y0-thickness+1; i<=y0+thickness-1; i++)
			for(int j=x0-thickness+1; j<=x0+thickness-1; j++)
				canvas->putPixelRGB(j, i, 0, 0, 0);
		
		if (x0==x1 && y0==y1) break;
			e2 = 2*err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

void Line::moveRight(int d) {
	point[0].moveRight(d);
	point[1].moveRight(d);
}

void Line::moveLeft(int d) {
	point[0].moveLeft(d);
	point[1].moveLeft(d);
}

void Line::moveUp(int d) {
	point[0].moveUp(d);
	point[1].moveUp(d);
}

void Line::moveDown(int d) {
	point[0].moveDown(d);
	point[1].moveDown(d);
}

void Line::moveRightDown(int dx, int dy) {
	point[0].moveRightDown(dx, dy);
	point[1].moveRightDown(dx, dy);
}
