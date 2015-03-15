#include "peta3d.h"

Peta3D::Peta3D()  : INSIDE(0), LEFT(1), RIGHT(2), BOTTOM(4), TOP(8), highlightedArea(Point(0,0)) {
	this->loadPeta2d("pulau/jawa.info");
	this->loadPeta2d("pulau/kalimantan.info");
	this->loadPeta2d("pulau/papuaRevB.info");
	this->loadPeta2d("pulau/sulawesiRevA.info");
	this->loadPeta2d("pulau/sumatra.info");
<<<<<<< HEAD
	this->loadPeta2d("pulau/bali.info");
=======
	this->loadPeta2d("pulau/malukuUtara.info");
	this->loadPeta2d("pulau/malukuUtara.info");
>>>>>>> b20de9e80c28e0d916365a6e32ab460cc0be8dad
	Point p1(0,0);
	Point p2(100,0);
	Point p3(100,100);
	Point p4(0,100);
	highlightedArea.addPoint(p1);
	highlightedArea.addPoint(p2);
	highlightedArea.addPoint(p3);
	highlightedArea.addPoint(p4);
	generetePeta3dSurfaces();
	generetePeta3dFromSurface();

	relativePositionX = 0;
	relativePositionY = 0;
}

void Peta3D::findTheShit() {
	const string nama_pulau[] = {"jawa", "kalimantan", "papua", "sulawesi", "sumatera"};

	int counter = 0;
	for (vector<Polygon>::iterator it = peta2d.begin(); it != peta2d.end(); it++, counter++) {
		cout << nama_pulau[counter] << endl;

		int x_min = it->getMostLeftPoint().getAbsis(),
			x_max = it->getMostRightPoint().getAbsis(),
			y_min = it->getMostUpperPoint().getOrdinat(),
			y_max = it->getMostBottomPoint().getOrdinat();

		cout << "(" << x_min << ", " << y_min << "), ";
		cout << "(" << x_max << ", " << y_max << ")" << endl;

		cout << endl;
	}
}

void Peta3D::drawPeta(Canvas* canvas) {
	for(vector<Polygon>::iterator it = petaSurface.begin(); it != petaSurface.end(); ++it) {
		it->drawBackground(canvas, canvas->pixel_color(255,0,0));
	}
}

void Peta3D::drawPeta3d(Canvas* canvas){
	for(vector<Line>::iterator it = peta3d.begin(); it != peta3d.end(); ++it) {
		it->draw(canvas, 1, canvas->pixel_color(255,255,255));
	}
}

void Peta3D::drawPetaClipping(Canvas *canvas) {
	int x = canvas->get_vinfo().xres;
	int y = canvas->get_vinfo().yres;
	// printf("%d %d\n",x,y);
	x--;y--;
	Polygon tmp;
	Point p1a(0,0);
	Point p2a(x,0);
	Point p3a(x,y);
	Point p4a(0,y);
	tmp.addPoint(p1a);
	tmp.addPoint(p2a);
	tmp.addPoint(p3a);
	tmp.addPoint(p4a);
	viewFrame = tmp;
	viewFrame.draw(canvas, canvas->pixel_color(255,0,0));
	for(vector<Line>::iterator it = peta3d.begin(); it != peta3d.end(); ++it) {
		CohenSutherlandLineClipAndDraw(it->getPointOne(), it->getPointTwo(), canvas);
	}
}

void Peta3D::loadPeta2d(const char* filename) {
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
	peta2d.push_back(polygon);
	fclose(file);
}

vector<Polygon> Peta3D::polygonTo3D(Polygon* polygon, int dy) {
	vector<Point> bottomPoints = polygon->getPoints();
	vector<Point> upperPoints = polygon->getPoints();

	for (int i=0; i<bottomPoints.size(); i++) {
		bottomPoints[i].move(0, dy);
	}

	vector<Polygon> retPol;
	for (int i=1; i<bottomPoints.size(); i++) {
		Polygon temp(Point(0,0));
		temp.addPoint(upperPoints[i]);
		temp.addPoint(bottomPoints[i]);
		temp.addPoint(bottomPoints[i-1]);
		temp.addPoint(upperPoints[i-1]);
		retPol.push_back(temp);
	}
	Polygon temp(Point(0,0));
	temp.addPoint(upperPoints[0]);
	temp.addPoint(bottomPoints[0]);
	temp.addPoint(bottomPoints[bottomPoints.size()-1]);
	temp.addPoint(upperPoints[bottomPoints.size()-1]);
	retPol.push_back(temp);

	//sort polygon
	sort(retPol.begin(), retPol.end(), Polygon::sortTopLeft);
	retPol.push_back(*polygon);

	return retPol;
}

void Peta3D::generetePeta3dSurfaces(){
	for(int i=0; i<peta2d.size(); i++) {
		vector<Polygon> surfaceFromOnePolygon = polygonTo3D(&(peta2d[i]), 10);
		petaSurface.insert(petaSurface.end(), surfaceFromOnePolygon.begin(), surfaceFromOnePolygon.end());
	}
}

void Peta3D::generetePeta3dFromSurface(){
	for(int i=0; i<petaSurface.size(); i++){
		vector<Line> hiddenLineRemoved;
		vector<Point> poly = petaSurface[i].getPoints();
		if(poly.size()>0)
			poly.push_back(poly[0]);

		//Untuk setiap garis yang telah ada, cek hiddenLineRemoval dengan surface baru
		for(int j=0; j<peta3d.size(); j++){
			vector<Point> daftar;

			daftar.push_back(peta3d[j].getPointOne());
			daftar.push_back(peta3d[j].getPointTwo());

			//Cek perpotongan garis dengan setiap sisi poligon
			for(int k=0; k<poly.size()-1; k++) {
				if((Point::orientation(peta3d[j].getPointOne(), peta3d[j].getPointTwo(), poly[k]) < 2 && Point::orientation(peta3d[j].getPointOne(), peta3d[j].getPointTwo(), poly[k+1]) == 2) ||
				   (Point::orientation(peta3d[j].getPointOne(), peta3d[j].getPointTwo(), poly[k]) == 2 && Point::orientation(peta3d[j].getPointOne(), peta3d[j].getPointTwo(), poly[k+1]) < 2)){
					Line ltemp(poly[k], poly[k+1]);
					Point* p;
					p=NULL;
					p = peta3d[j].getIntersectionPointWith(ltemp);

					if (p!=NULL) {
						daftar.push_back(*p);
						free(p);
					}
				}
			}

			sort(daftar.begin(), daftar.end(), Point::pointGreaterThan);

			for(int k=0; k+1<daftar.size(); k++){
				int midX = (daftar[k].getAbsis()+ daftar[k+1].getAbsis())/2;
				int midY = (daftar[k].getOrdinat()+ daftar[k+1].getOrdinat())/2;


				Point midPoint = Point(midX , midY);
				if(!petaSurface[i].isPointInside(midPoint)) {
					hiddenLineRemoved.push_back(Line(daftar[k], daftar[k+1]));
				}

			}

		}

		peta3d = hiddenLineRemoved;
		vector<Line> newLines = petaSurface[i].getLines();
		peta3d.insert(peta3d.end(), newLines.begin(), newLines.end());
	}
}

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (xmin, ymin), and (xmax, ymax)

OutCode Peta3D::ComputeOutCode(int x, int y, int xmin, int ymin, int xmax, int ymax) {
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
void Peta3D::CohenSutherlandLineClipAndDraw(Point p0, Point p1, Canvas* canvas) {
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

void Peta3D::scaleAndDraw(Canvas* canvas, Point p0, Point p1) {
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

void Peta3D::move(int dx, int dy){
	if(abs(relativePositionX+dx) <100 && abs(relativePositionY+dy) <100){
		relativePositionX += dx;
		relativePositionY += dy;
		for(int i=0; i<peta3d.size(); i++){
			peta3d[i].move(dx, dy);
		}
	}
}

void Peta3D::zoomOut(Canvas* canvas) {
	int canvasX = canvas->get_vinfo().xres;
	int canvasY = canvas->get_vinfo().yres;
	
	int highlightedAreaWidth = highlightedArea.getMaxX() - highlightedArea.getMinX();
	int highlightedAreaHeighth = highlightedArea.getMaxY() - highlightedArea.getMinY();
	Polygon newhighlightedArea = highlightedArea.resizing (1.10, highlightedAreaWidth/2, highlightedAreaHeighth/2);
	int minX = newhighlightedArea.getMinX();
	int minY = newhighlightedArea.getMinY();
	int maxX = newhighlightedArea.getMaxX();
	int maxY = newhighlightedArea.getMaxY();
	if (minX > 0 && minY > 0 && maxX < canvasX && maxY < canvasY) {
		highlightedArea = newhighlightedArea;
	}
}


void Peta3D::zoomIn() {
	int highlightedAreaWidth = highlightedArea.getMaxX() - highlightedArea.getMinX();
	int highlightedAreaHeighth = highlightedArea.getMaxY() - highlightedArea.getMinY();
	Polygon newhighlightedArea = highlightedArea.resizing (0.90, highlightedAreaWidth/2, highlightedAreaHeighth/2);
	int minX = newhighlightedArea.getMinX();
	int minY = newhighlightedArea.getMinY();
	int maxX = newhighlightedArea.getMaxX();
	int maxY = newhighlightedArea.getMaxY();
	int newhighlightedAreaWidth = maxX - minX;
	int newhighlightedAreaHeight = maxY - minY;
	if (newhighlightedAreaHeight >= 50 && newhighlightedAreaWidth >= 50) {
		highlightedArea = newhighlightedArea;
	}
}

void Peta3D::moveHighlightedArea(int dx, int dy, Canvas *canvas) {
	int min_x = highlightedArea.getMinX(), max_x = highlightedArea.getMaxX(),
		min_y = highlightedArea.getMinY(), max_y = highlightedArea.getMaxY();
	int canvasX = canvas->get_vinfo().xres;
	int canvasY = canvas->get_vinfo().yres;
	// cout << min_x << " " << min_y << " " << max_x << " " << max_y << endl;
	// cout << canvasX << " " << canvasY << endl;
	// getchar();
	if (dx < 0) {
		// dx = abs(dx);
		// cout << " m " << endl;
		if (min_x + dx >= 0) { 
			highlightedArea.move(dx,0);
		} else {
			highlightedArea.move(-1*min_x,0);
		}
	} else if (dx > 0) {
		// cout << " n " << endl;
		if (max_x + dx < canvasX) {
			highlightedArea.move(dx, 0);
		} else {
			highlightedArea.move(canvasX - max_x, 0);
		}
	}

	if (dy < 0) {
		// dy = abs(dy);
		// cout << " o " << endl;
		if (min_y + dy >= 0) {
			highlightedArea.move(0, dy);
		} else {
		 	highlightedArea.move(0, -1*min_y);
		}
	} else if (dy > 0) {
		// cout << " p " << endl;
		if (max_y + dy < canvasY) {
			highlightedArea.move(0, dy);
		} else {
			highlightedArea.move(0, canvasY - max_y);
		}
	}
}
