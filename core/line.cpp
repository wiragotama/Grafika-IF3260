#include "line.h"
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

void Line::draw(Canvas *canvas, int thickness, uint32_t color) {
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

void Line::drawBackground(Canvas *canvas, int thickness, uint32_t color) {
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
				canvas->putBackgroundPixel(j, i, color);

		if (x0==x1 && y0==y1) break;
			e2 = 2*err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

void Line::drawCurve(Canvas *canvas, int thickness, uint32_t color) {
/* based on bezier curve bresenham */
	int x0, x1, x2, y0, y1, y2;

	x0 = point[0].getAbsis();
	y0 = point[0].getOrdinat();

	x2 = point[1].getAbsis();
	y2 = point[1].getOrdinat();

	x1 = (x0+x2)/2;
	x1 = (x0+x1)/2;
	y1 = (y0+y2)/2;
	y1 = (y1+y2)/2;


	int sx = x2-x1, sy = y2-y1;
	long xx = x0-x1, yy = y0-y1, xy;         /* relative values for checks */
	double dx, dy, err, cur = xx*sy-yy*sx;                    /* curvature */

	assert(xx*sx <= 0 && yy*sy <= 0);  /* sign of gradient must not change */

	if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy) { /* begin with longer part */
		x2 = x0; x0 = sx+x1; y2 = y0; y0 = sy+y1; cur = -cur;  /* swap P0 P2 */
	}
	if (cur != 0) {                                    /* no straight line */
		xx += sx; xx *= sx = x0 < x2 ? 1 : -1;           /* x step direction */
		yy += sy; yy *= sy = y0 < y2 ? 1 : -1;           /* y step direction */
		xy = 2*xx*yy; xx *= xx; yy *= yy;          /* differences 2nd degree */
		if (cur*sx*sy < 0) {                           /* negated curvature? */
			xx = -xx; yy = -yy; xy = -xy; cur = -cur;
		}
		dx = 4.0*sy*cur*(x1-x0)+xx-xy;             /* differences 1st degree */
		dy = 4.0*sx*cur*(y0-y1)+yy-xy;
		xx += xx; yy += yy; err = dx+dy+xy;                /* error 1st step */
		do {
			//setPixel(x0,y0);                                     /* plot curve */
			for(int i=y0-thickness+1; i<=y0+thickness-1; i++)
				for(int j=x0-thickness+1; j<=x0+thickness-1; j++)
					canvas->putPixelColor(j, i, color);
			if (x0 == x2 && y0 == y2) return;  /* last pixel -> curve finished */
			y1 = 2*err < dx;                  /* save value for test of y step */
			if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
			if (    y1    ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
		} while (dy < dx );           /* gradient negates -> algorithm fails */
	}
	else {
		draw(canvas, thickness, color);
	}
}

void Line::drawCurveBackground(Canvas *canvas, int thickness, uint32_t color) {
/* based on bezier curve bresenham */
	int x0, x1, x2, y0, y1, y2;

	x0 = point[0].getAbsis();
	y0 = point[0].getOrdinat();

	x2 = point[1].getAbsis();
	y2 = point[1].getOrdinat();

	x1 = (x0+x2)/2;
	x1 = (x0+x1)/2;
	y1 = (y0+y2)/2;
	y1 = (y1+y2)/2;


	int sx = x2-x1, sy = y2-y1;
	long xx = x0-x1, yy = y0-y1, xy;         /* relative values for checks */
	double dx, dy, err, cur = xx*sy-yy*sx;                    /* curvature */

	assert(xx*sx <= 0 && yy*sy <= 0);  /* sign of gradient must not change */

	if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy) { /* begin with longer part */
		x2 = x0; x0 = sx+x1; y2 = y0; y0 = sy+y1; cur = -cur;  /* swap P0 P2 */
	}
	if (cur != 0) {                                    /* no straight line */
		xx += sx; xx *= sx = x0 < x2 ? 1 : -1;           /* x step direction */
		yy += sy; yy *= sy = y0 < y2 ? 1 : -1;           /* y step direction */
		xy = 2*xx*yy; xx *= xx; yy *= yy;          /* differences 2nd degree */
		if (cur*sx*sy < 0) {                           /* negated curvature? */
			xx = -xx; yy = -yy; xy = -xy; cur = -cur;
		}
		dx = 4.0*sy*cur*(x1-x0)+xx-xy;             /* differences 1st degree */
		dy = 4.0*sx*cur*(y0-y1)+yy-xy;
		xx += xx; yy += yy; err = dx+dy+xy;                /* error 1st step */
		do {
			//setPixel(x0,y0);                                     /* plot curve */
			for(int i=y0-thickness+1; i<=y0+thickness-1; i++)
				for(int j=x0-thickness+1; j<=x0+thickness-1; j++)
					canvas->putBackgroundPixel(j, i, color);
			if (x0 == x2 && y0 == y2) return;  /* last pixel -> curve finished */
			y1 = 2*err < dx;                  /* save value for test of y step */
			if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
			if (    y1    ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
		} while (dy < dx );           /* gradient negates -> algorithm fails */
	}
	else {
		drawBackground(canvas, thickness, color);
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

void Line::move(int dx, int dy) {
	point[0].move(dx, dy);
	point[1].move(dx, dy);
}

bool Line::onSegmentIfColinear(Point q){
	Point p = this->point[0];
	Point r = this->point[1];
    if (q.getAbsis() <= max(p.getAbsis(), r.getAbsis()) &&
		q.getAbsis() >= min(p.getAbsis(), r.getAbsis()) &&
		q.getOrdinat() <= max(p.getOrdinat(), r.getOrdinat()) &&
		q.getOrdinat() >= min(p.getOrdinat(), r.getOrdinat())	)
       return true;

    return false;
}

bool Line::isIntersectWith(Line l2) {
    // Find the four orientations needed for general and
    // special cases
    Point p1 = this->point[0];
    Point q1 = this->point[1];
    Point p2 = l2.getPointOne();
    Point q2 = l2.getPointTwo();
    int o1 = Point::orientation(p1, q1, p2);
    int o2 = Point::orientation(p1, q1, q2);
    int o3 = Point::orientation(p2, q2, p1);
    int o4 = Point::orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    return false; // Doesn't fall in any of the above cases
}


Point* Line::getIntersectionPointWith(Line line) {
	if (!this->isIntersectWith(line)) return NULL;
	Point p1 = this->point[0];
	Point p2 = this->point[1];
	Point p3 = line.getPointOne();
	Point p4 = line.getPointTwo();
	// menjamin pasti telah intersection dengan line tersebut
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.getAbsis(), x2 = p2.getAbsis(), x3 = p3.getAbsis(), x4 = p4.getAbsis();
	float y1 = p1.getOrdinat(), y2 = p2.getOrdinat(), y3 = p3.getOrdinat(), y4 = p4.getOrdinat();
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	//~ if (d == 0)
		//~ return NULL;

	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
	// Check if the x and y coordinates are within both lines
	//~ if ( x < min(x1, x2) || x > max(x1, x2) ||
	//~ x < min(x3, x4) || x > max(x3, x4) ) return NULL;
	//~ if ( y < min(y1, y2) || y > max(y1, y2) ||
	//~ y < min(y3, y4) || y > max(y3, y4) ) return NULL;
	// Return the point of intersection
	Point *ret = new Point(x,y);
	return ret;
}

int Line::getDifXInVector() const {
	int x0 = this->point[0].getAbsis();
	int x1 = this->point[1].getAbsis();
	return x0-x1;
}

int Line::getDifYInVector() const {
	int y0 = this->point[0].getOrdinat();
	int y1 = this->point[1].getOrdinat();
	return y0-y1;
}

double Line::getLength() const {
	double a = this->getDifXInVector();
	double b = this->getDifYInVector();
	return sqrt(a*a + b*b);
}

double Line::angle(Point a, Point o, Point b) {
	// printf("sekarang masuk angle "); a.printInfo(); o.printInfo(); b.printInfo();cout<<endl;
	 Line l1(a,o);
	 Line l2(b,o);
	 double length1 = l1.getLength();
	 double length2 = l2.getLength();
	 double tmp = l1.getDifXInVector() * l2.getDifXInVector() + l1.getDifYInVector() * l2.getDifYInVector();
	 // cout << l1.getDifXInVector() << " " << l2.getDifXInVector() << " " << l1.getDifYInVector() << " " << l2.getDifYInVector() << endl;
	 // cout << length1 << " " << length2 << " " << tmp << endl;
	 double haha = 0;
	 if (length1 < EPS || length2 < EPS) { //berarti point tersebut sama
	 	haha = 1; //biar di acos jadi 0;
	 } else {
	 	haha = (double)tmp/(length1 * length2);
	 	if (haha > 1.0) haha = 1.0;
	 	else if (haha < -1.0) haha = -1.0;
	 }
	 return acos(haha); //return dalam radian
}
