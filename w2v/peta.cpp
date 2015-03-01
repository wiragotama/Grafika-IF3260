#include "peta.h"

Peta::Peta() : INSIDE(0), LEFT(1), RIGHT(2), BOTTOM(4), TOP(8), highlightedArea(Point(0,0)) {
	this->loadFile("pulau/jawa.info");
	this->loadFile("pulau/kalimantan.info");
	this->loadFile("pulau/papua.info");
	this->loadFile("pulau/sulawesi.info");
	this->loadFile("pulau/sumatera.info");
	Point p1(0,0);
	Point p2(100,0);
	Point p3(100,100);
	Point p4(0,100);
	highlightedArea.addPoint(p1);
	highlightedArea.addPoint(p2);
	highlightedArea.addPoint(p3);
	highlightedArea.addPoint(p4);

	Point p1a(500,350);
	Point p2a(600,350);
	Point p3a(600,450);
	Point p4a(500,450);
	viewFrame.addPoint(p1a);
	viewFrame.addPoint(p2a);
	viewFrame.addPoint(p3a);
	viewFrame.addPoint(p4a);
}

Peta::~Peta() {}

void Peta::drawIndonesia(Canvas *canvas) {
	for(vector<Polygon>::iterator it = islands.begin(); it != islands.end(); ++it) {
		it->drawBackground(canvas, canvas->pixel_color(255,0,0));
		vector<Point> points = it->getPoints();
		for (vector<Point>::iterator it1 = points.begin(); it1 != points.end(); ++it1) {
			if (it1+1 != points.end()) {
				CohenSutherlandLineClipAndDraw(*it1, *(it1+1), canvas);
			} else {
				CohenSutherlandLineClipAndDraw(*it1, points.front(), canvas);
			}
		}
	}
	drawViewFrame(canvas);
}

void Peta::zoomOut() {
	Point p = highlightedArea.getTopLeftPosition();
	p.move(-1,-1);
	highlightedArea.setTopLeftPosition(p);
	
	p = highlightedArea.getPoint(1);
	p.moveRight(2);
	highlightedArea.setPoint(1, p);

	p = highlightedArea.getPoint(2);
	p.move(2,2);
	highlightedArea.setPoint(2, p);

	p = highlightedArea.getPoint(3);
	p.moveDown(2);
	highlightedArea.setPoint(3, p);
}


void Peta::zoomIn() {	
	Point p = highlightedArea.getTopLeftPosition();
	p.move(1,1);
	highlightedArea.setTopLeftPosition(p);
	
	p = highlightedArea.getPoint(1);
	p.moveLeft(2);
	highlightedArea.setPoint(1, p);

	p = highlightedArea.getPoint(2);
	p.move(-2,-2);
	highlightedArea.setPoint(2, p);

	p = highlightedArea.getPoint(3);
	p.moveUp(2);
	highlightedArea.setPoint(3, p);
}

void Peta::drawViewFrame(Canvas* canvas) {
	viewFrame.draw(canvas, canvas->pixel_color(0,255,0));
}

void Peta::showHighlightedArea(Canvas* canvas) {
	highlightedArea.draw(canvas, canvas->pixel_color(0,255,255));
}

void Peta::moveHighlightedArea(char c, Canvas* canvas) {
	int min_x = highlightedArea.getMinX(), max_x = highlightedArea.getMaxX(),
		min_y = highlightedArea.getMinY(), max_y = highlightedArea.getMaxY();

	if (c == 97 && min_x > 0) { //left gradient
		highlightedArea.move(-1,0);
	}
	else if (c == 119 && min_y > 0) { //up gradient
		highlightedArea.move(0,-1);
	}
	else if (c == 100 && max_x < 640) { //right gradient
		highlightedArea.move(1,0);
	}
	else if (c == 115 && max_y < 480) { //down gradient
		highlightedArea.move(0,1);
	} else if (c == 45 && min_x > 0 && min_y > 0 && max_x < 640 && max_y < 480) { //zoomout //tanda (-)
		this->zoomOut();
	} else if (c == 43) {
		this->zoomIn();
	}

	highlightedArea.draw(canvas, canvas->pixel_color(0,255,255));
}

void Peta::loadFile(const char *filename) {
	int count, p1, p2;
	uint32_t value;
	FILE *file;
	file = fopen(filename,"r");
	fscanf(file, "%d", &count);
	Polygon polygon(Point(0,0));

	for(int it=0; it<count ; ++it) {
		fscanf(file, "%d %d", &p1, &p2);
		Point p(p1,p2);
		polygon.addPoint(p);
	}
	islands.push_back(polygon);
	fclose(file);
}

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (xmin, ymin), and (xmax, ymax)

// ASSUME THAT xmax, xmin, ymax and ymin are global constants.

OutCode Peta::ComputeOutCode(int x, int y, int xmin, int ymin, int xmax, int ymax) {
	OutCode code;

	code = INSIDE;          // initialised as being inside of clip window
 	// printf("Code gw jing %d\n", code);

	if (x < xmin)           // to the left of clip window
		code |= LEFT;
	else if (x > xmax)      // to the right of clip window
		code |= RIGHT;

	if (y < ymin)           // below the clip window
		code |= BOTTOM;
	else if (y > ymax)      // above the clip window
		code |= TOP;

	return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
// diagonal from (xmin, ymin) to (xmax, ymax).
void Peta::CohenSutherlandLineClipAndDraw(Point p0, Point p1, Canvas* canvas) {
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle

	int x0 = p0.getAbsis();
	int y0 = p0.getOrdinat();
	int x1 = p1.getAbsis();
	int y1 = p1.getOrdinat();

	int xmin = highlightedArea.getMinX();
	int ymin = highlightedArea.getMinY();
	int xmax = highlightedArea.getMaxX();
	int ymax = highlightedArea.getMaxY();

	OutCode outcode0 = ComputeOutCode(x0, y0, xmin, ymin, xmax, ymax);
	OutCode outcode1 = ComputeOutCode(x1, y1, xmin, ymin, xmax, ymax);

	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
			accept = true;
			break;
		} else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			int x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

			// Now find the intersection point;
			// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
			if (outcodeOut & TOP) {           // point is above the clip rectangle
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0, xmin, ymin, xmax, ymax);
			} else { // outcodeOut == outcode1
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1, xmin, ymin, xmax, ymax);
			}
		}
	}


	if (accept) {
		//jadi dapat (x0,y0) dan (x1,y1), yaitu point hasil clipping ke highlighted area
		//setelah itu, scaling ke view frame
		scaleAndDraw(canvas, Point(x0,y0), Point(x1,y1));
	}
}

void Peta::scaleAndDraw(Canvas* canvas, Point p0, Point p1) {
	int x0 = p0.getAbsis();
	int y0 = p0.getOrdinat();

	int x1 = p1.getAbsis();
	int y1 = p1.getOrdinat();

	float xfactor = (float)(viewFrame.getMaxX() - viewFrame.getMinX())/(highlightedArea.getMaxX() - highlightedArea.getMinX());
	float yfactor = (float)(viewFrame.getMaxY() - viewFrame.getMinY())/(highlightedArea.getMaxY() - highlightedArea.getMinY());

	int x0new = (int) (xfactor * (x0 - highlightedArea.getMinX())) + viewFrame.getMinX(); 
	int y0new = (int) (yfactor * (y0 - highlightedArea.getMinY())) + viewFrame.getMinY();
	int x1new = (int) (xfactor * (x1 - highlightedArea.getMinX())) + viewFrame.getMinX(); 
	int y1new = (int) (yfactor * (y1 - highlightedArea.getMinY())) + viewFrame.getMinY();

	Line l(Point(x0new,y0new), Point(x1new,y1new));
	l.drawBackground(canvas, 1, canvas->pixel_color(255,0,0));
}