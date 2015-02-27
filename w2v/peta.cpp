#include "peta.h"

Peta::Peta() : INSIDE(0), LEFT(1), RIGHT(2), BOTTOM(4), TOP(8) {
	this->loadFile("pulau/jawa.info");
	this->loadFile("pulau/kalimantan.info");
	this->loadFile("pulau/papua.info");
	this->loadFile("pulau/sulawesi.info");
	this->loadFile("pulau/sumatera.info");
	this->size_width = 480;
	this->size_height = 320;
}

Peta::~Peta() {}

void Peta::windowToView(Canvas *canvas) {
	for(vector<Polygon>::iterator it = islands.begin(); it != islands.end(); ++it) {
		it->draw(canvas, canvas->pixel_color(255,0,0));
	}

}

void Peta::showSmallViewFrame(Canvas *canvas){
	Point p1(500,350);
	Point p2(600,350);
	Point p3(600,450);
	Point p4(500,450);
	smallViewFrame.addPoint(p1);
	smallViewFrame.addPoint(p2);
	smallViewFrame.addPoint(p3);
	smallViewFrame.addPoint(p4);
	smallViewFrame.draw(canvas, canvas->pixel_color(0,255,0));
}

void Peta::showHighlightedArea(Canvas* canvas) {
	Point p1(0,0);
	Point p2(100,0);
	Point p3(100,100);
	Point p4(0,100);
	highlightedArea.addPoint(p1);
	highlightedArea.addPoint(p2);
	highlightedArea.addPoint(p3);
	highlightedArea.addPoint(p4);
	highlightedArea.draw(canvas, canvas->pixel_color(0,255,255));
}

void Peta::moveHighlightedArea(char c,Canvas* canvas) {
	if(c==97 && highlightedArea.getMostLeftPoint().getAbsis()>0) {//left gradient
		highlightedArea.move(-1,0);
	}
	else if (c==119 && highlightedArea.getMostUpperPoint().getOrdinat()>0) { //up gradient
		highlightedArea.move(0,-1);
	}
	else if (c==100 && highlightedArea.getMostRightPoint().getAbsis()<640) { //right gradient
		highlightedArea.move(1,0);
	}
	else if (c==115 && highlightedArea.getMostBottomPoint().getOrdinat()<480) { //down gradient
		highlightedArea.move(0,1);
	}
	
	highlightedArea.draw(canvas, canvas->pixel_color(0,255,255));
}

void Peta::loadFile(const char *filename) {
	int count, p1, p2;
	uint32_t value;
	FILE *file;
	file = fopen(filename,"r");
	fscanf(file, "%d", &count);
	Polygon polygon;

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
 
OutCode Peta::ComputeOutCode(int x, int y) {
	OutCode code;
 
	code = INSIDE;          // initialised as being inside of clip window
 
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
void Peta::CohenSutherlandLineClipAndDraw(int x0, int y0, int x1, int y1) {
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = ComputeOutCode(x0, y0);
	OutCode outcode1 = ComputeOutCode(x1, y1);
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
				outcode0 = ComputeOutCode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}
	}
	if (accept) {
               // Following functions are left for implementation by user based on
               // their platform (OpenGL/graphics.h etc.)
               // DrawRectangle(xmin, ymin, xmax, ymax);
               // LineSegment(x0, y0, x1, y1);
	}
}

