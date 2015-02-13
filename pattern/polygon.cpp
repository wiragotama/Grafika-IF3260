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
	floodFill(firePoint.getAbsis(), firePoint.getOrdinat());
	canvas->putPixelColor(firePoint.getAbsis()+topLeftPosition.getAbsis(), firePoint.getOrdinat()+topLeftPosition.getOrdinat(), canvas->pixel_color(255,0,0));
	canvas->flush();
}

void Polygon::floodFill(int x, int y) {
	long location = canvas->getCursorLocation(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat());
	if ((x>=0 && x<canvas->get_vinfo().xres) && (y>=0 && y<canvas->get_vinfo().yres) && (canvas->getColor(location) >>24!=0xff)) {
		canvas->putPixelColor(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat(), getColor(x,y));
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
}

void Polygon::loadPattern(const char *filename) {
	pattern.loadFile(filename);
}

uint32_t Polygon::getColor(int x, int y) {
	int i = x % pattern.getWidth();
	int j = y % pattern.getHeight();
	/*printf("%d\n", canvas->pixel_color(255,0,0));
	if (pattern.getColor(j, i)==canvas->pixel_color(255,0,0)) {
		system("pause");
	}*/
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
