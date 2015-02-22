#include "../pattern/polygon.h"

Polygon::Polygon(Canvas *canvas, Point topLeftPosition) {
	this->canvas = canvas;
	this->topLeftPosition = topLeftPosition;
}

Polygon::~Polygon() {
}

void Polygon::draw() {
	
	for (int i=1; i<points.size(); i++) {
		Line line(points[i], points[i-1]);
		line.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
		line.draw(canvas, 1.0, canvas->pixel_color(255,0,0));
	}
	Line line(points[points.size()-1], points[0]);
	line.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
	line.draw(canvas, 1.0, canvas->pixel_color(255,0,0));
	
	//flood fill
	if (pattern.getMatrix()!=NULL)
		floodFill(firePoint.getAbsis(), firePoint.getOrdinat());
	canvas->flush();
}

void Polygon::floodFill(int x, int y) {
	long location = canvas->getCursorLocation(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat());
	int dx = originFirePoint.getAbsis()-firePoint.getAbsis(), dy = originFirePoint.getOrdinat()-firePoint.getOrdinat();
	
	int screen_x = x + topLeftPosition.getAbsis();
	int screen_y = y + topLeftPosition.getOrdinat();
	
	if ((screen_x>=0 && screen_x<canvas->get_vinfo().xres) && (screen_y>=0 && screen_y<canvas->get_vinfo().yres) && (canvas->getColor(location) >>24!=0xff)) {
		canvas->putPixelColor(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat(), getColor(x+dx, y+dy));
		floodFill(x-1, y);
		floodFill(x+1, y);
		floodFill(x, y-1);
		floodFill(x, y+1);
	}
}

void Polygon::move(int dx, int dy) {
	for (int i=0; i<points.size(); i++)
		points[i].move(dx, dy);
	
	firePoint.move(dx, dy);
	topLeftPosition.move(dx, dy);
}

void Polygon::loadPolygon(const char* filename) {
	int numPoints, x, y;
	FILE *matrix_file;
	matrix_file = fopen(filename,"r");

	fscanf(matrix_file, "%d", &numPoints);

	for (int i=0; i<numPoints; i++) {
		fscanf(matrix_file, "%d %d", &x, &y);
		Point P(x,y);
		points.push_back(P);
	}
	
	fscanf(matrix_file,"%d %d",&x, &y);
	firePoint = Point(x,y);
	originFirePoint = firePoint;
}

void Polygon::loadPattern(const char *filename) {
	pattern.loadFile(filename);
}

uint32_t Polygon::getColor(int x, int y) {
	while (x<0) x+=pattern.getWidth();
	while (y<0) y+=pattern.getHeight();
	int i = x % pattern.getWidth();
	int j = y % pattern.getHeight();
	return pattern.getColor(j, i);
}

/* Setter & Getter */
void Polygon::setPoint(int idx, Point P) {
	points[idx] = P;
}

void Polygon::setFirePoint(Point P) {
	firePoint = P;
}

void Polygon::setTopLeftPosition(int x, int y) {
	topLeftPosition.setAbsis(x);
	topLeftPosition.setOrdinat(y);
}

Point Polygon::getPoint(int idx) {
	return points[idx];
}

Point Polygon::getFirePoint() {
	return firePoint;
}

Point Polygon::getTopLeftPosition() {
	return topLeftPosition;
}

Point Polygon::getMostRightPoint() {
	int x = 0;
	int idx = 0;
	for (int it=0; it<points.size(); ++it) {
		if (points[it].getAbsis()>=x) {
			x = points[it].getAbsis();
			idx = it;
		}
	}
	return points[idx];
}

Point Polygon::getMostLeftPoint() {
	int x = 10000;
	int idx = 0;
	for (int it=0; it<points.size(); ++it) {
		if (points[it].getAbsis()<=x) {
			x = points[it].getAbsis();
			idx = it;
		}
	}
	return points[idx];
}

Point Polygon::getMostBottomPoint() {
	int x = 0;
	int idx = 0;
	for (int it=0; it<points.size(); ++it) {
		if (points[it].getOrdinat()>=x) {
			x = points[it].getOrdinat();
			idx = it;
		}
	}
	return points[idx];
}

Point Polygon::getMostUpperPoint() {
	int x = 10000;
	int idx = 0;
	for (int it=0; it<points.size(); ++it) {
		if (points[it].getOrdinat()<=x) {
			x = points[it].getOrdinat();
			idx = it;
		}
	}
	return points[idx];
}
