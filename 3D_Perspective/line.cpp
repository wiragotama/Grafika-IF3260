#include "line.h"

/*************************/
/* Method implementation */
/*************************/

Line::Line(Point P1, Point P2){
	this->point[0] = P1;
	this->point[1] = P2;
}

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

void Line::draw(Canvas *canvas, int thickness, uint32_t color) {
	int x1 = round(point[1].getAbsis());
	int x0 = round(point[0].getAbsis());

	int y1 = round(point[1].getOrdinat());
	int y0 = round(point[0].getOrdinat());

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
