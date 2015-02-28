#include "../pattern/polygon.h"

const int MAXINT = 0x7FFFFFFF;

Polygon::Polygon() {}

Polygon::Polygon(Point topLeftPosition) {
	this->topLeftPosition = topLeftPosition;
}

Polygon::Polygon(Point topLeftPosition, vector<Point> nodes, Point firePoint, Pattern pattern_t) : pattern(pattern_t) {
    this->topLeftPosition = topLeftPosition;
    points = nodes;
    this->firePoint = firePoint;
    originFirePoint = firePoint;
}

Polygon::~Polygon() {
	while (points.size()>0)
		points.erase(points.begin());
}

Polygon::Polygon(const Polygon& ply) : pattern(ply.getPattern()) {
	points = ply.getPoints();
	firePoint = ply.getFirePoint();
	originFirePoint = ply.getOriginFirePoint();
	topLeftPosition = ply.getTopLeftPosition();
}

const Polygon& Polygon::operator=(const Polygon& ply) {
	points = ply.getPoints();
	pattern = ply.getPattern();
	firePoint = ply.getFirePoint();
	originFirePoint = ply.getOriginFirePoint();
	topLeftPosition = ply.getTopLeftPosition();
	return *this;
}

int Polygon::getMaxY() const {
    if (max_y == -1) { // haven't computed yet
        vector<Point>::const_iterator it = points.begin();
        // it must have at least a point right?
        max_y = it->getOrdinat(); it++;

        while (it != points.end()) {
            int y = it->getOrdinat();
            if (y > max_y)
                max_y = y;
        }
    }
    return max_y+topLeftPosition.getOrdinat();
}

int Polygon::getMinY() const {
    if (min_y == -1) { // haven't computed yet
        vector<Point>::const_iterator it = points.begin();
        // it must have at least a point right?
        min_y = it->getOrdinat(); it++;

        while (it != points.end()) {
            int y = it->getOrdinat();
            if (y < min_y)
                min_y = y;
        }
    }
    return min_y+topLeftPosition.getOrdinat();
}

int Polygon::getMinX() const {
    if (min_x == -1) { // haven't computed yet
        vector<Point>::const_iterator it = points.begin();
        // it must have at least a point right?
        min_x = it->getAbsis(); it++;

        while (it != points.end()) {
            int x = it->getAbsis();
            if (x < min_x)
                min_x = x;
        }
    }
    return min_x+topLeftPosition.getAbsis();
}

int Polygon::getMaxX() const {
    if (max_x == -1) { // haven't computed yet
        vector<Point>::const_iterator it = points.begin();
        // it must have at least a point right?
        max_x = it->getAbsis(); it++;

        while (it != points.end()) {
            int x = it->getAbsis();
            if (x > max_x)
                max_x = x;
        }
    }
    return max_x+topLeftPosition.getAbsis();
}

Point Polygon::getOriginFirePoint() const {
	return originFirePoint;
}

vector<Point> Polygon::getPoints() const {
	return points;
}

Pattern Polygon::getPattern() const {
	return pattern;
}

void Polygon::printInfo() {
    printf("Polygon:");
    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        printf(" ");
        it->printInfo();
    }
    printf("\nFirePoint: ");
    firePoint.printInfo();
    printf("\n");
}

Polygon Polygon::rotate(double angle, int rx, int ry) {
    vector<Point> transformed = points;
    int min_x = MAXINT, min_y = MAXINT;
    // transformasi rotasi
    for (vector<Point>::iterator it = transformed.begin(); it != transformed.end(); it++) {
        it->rotate(angle, rx, ry);
        if (min_x > it->getAbsis())
            min_x = it->getAbsis();
        if (min_y > it->getOrdinat())
            min_y = it->getOrdinat();
    }

    // perbaiki top left
    Point newTopLeft = getTopLeftPosition();
    if (min_x < 0)
        newTopLeft.setAbsis(newTopLeft.getAbsis()+min_x);
    if (min_y < 0)
        newTopLeft.setOrdinat(newTopLeft.getOrdinat()+min_y);

    // normalisasi point (hanya berjalan jika terjadi perbaikan top left)
    for (vector<Point>::iterator it = transformed.begin(); it != transformed.end(); it++) {
        if (min_x < 0)
            it->setAbsis(it->getAbsis()-min_x);
        if (min_y < 0)
            it->setOrdinat(it->getOrdinat()-min_y);
    }

    Point transformedFirePoint = firePoint;
    transformedFirePoint.rotate(angle, rx, ry);
    if (min_x < 0)
        transformedFirePoint.setAbsis(transformedFirePoint.getAbsis() - min_x);
    if (min_y < 0)
        transformedFirePoint.setOrdinat(transformedFirePoint.getOrdinat() - min_y);

    return Polygon(newTopLeft, transformed, transformedFirePoint, pattern);
}

void Polygon::erasePoints() {
	while (points.size()>0)
		points.erase(points.begin());
}

void Polygon::draw(Canvas* canvas, uint32_t color) {

	for (int i=1; i<points.size(); i++) {
		Line line(points[i], points[i-1]);
		line.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
		line.draw(canvas, 1.0, color);
	}
	Line line(points[points.size()-1], points[0]);
	line.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
	line.draw(canvas, 1.0, color);

	//flood fill
	if (pattern.getMatrix()!=NULL)
		floodFill(canvas, firePoint.getAbsis(), firePoint.getOrdinat());

	int x = topLeftPosition.getAbsis();
	int y = topLeftPosition.getOrdinat();
	int x1 = x + getWidth();
	int y1 = y + getHeight();
	canvas->resetDirtyBit(x, y, x1, y1);
}

void Polygon::drawBackground(Canvas *canvas, uint32_t color) {
	for (int i=1; i<points.size(); i++) {
		Line line(points[i], points[i-1]);
		line.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
		line.drawBackground(canvas, 1.0, color);
	}
	Line line(points[points.size()-1], points[0]);
	line.move(topLeftPosition.getAbsis(), topLeftPosition.getOrdinat());
	line.drawBackground(canvas, 1.0, color);

	//flood fill
	if (pattern.getMatrix()!=NULL)
		floodFillBackground(canvas, firePoint.getAbsis(), firePoint.getOrdinat());
}

void Polygon::floodFill(Canvas* canvas, int x, int y) {
	long location = canvas->getCursorLocation(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat());
	int dx = originFirePoint.getAbsis()-firePoint.getAbsis(), dy = originFirePoint.getOrdinat()-firePoint.getOrdinat();

	int screen_x = x + topLeftPosition.getAbsis();
	int screen_y = y + topLeftPosition.getOrdinat();

	if ((screen_x>=0 && screen_x<canvas->get_vinfo().xres) && (screen_y>=0 && screen_y<canvas->get_vinfo().yres) && (canvas->getColor(location) >>24!=0xff)) {
		canvas->putPixelColor(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat(), getColor(x+dx, y+dy));
		floodFill(canvas, x-1, y);
		floodFill(canvas, x+1, y);
		floodFill(canvas, x, y-1);
		floodFill(canvas, x, y+1);
	}
}

void Polygon::floodFillBackground(Canvas* canvas, int x, int y) {
	long location = canvas->getCursorLocation(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat());
	int dx = originFirePoint.getAbsis()-firePoint.getAbsis(), dy = originFirePoint.getOrdinat()-firePoint.getOrdinat();

	int screen_x = x + topLeftPosition.getAbsis();
	int screen_y = y + topLeftPosition.getOrdinat();

	if ((screen_x>=0 && screen_x<canvas->get_vinfo().xres) && (screen_y>=0 && screen_y<canvas->get_vinfo().yres)) {
		canvas->putBackgroundPixel(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat(), getColor(x+dx, y+dy));
		floodFillBackground(canvas, x-1, y);
		floodFillBackground(canvas, x+1, y);
		floodFillBackground(canvas, x, y-1);
		floodFillBackground(canvas, x, y+1);
	}
}

void Polygon::move(int dx, int dy) {
	for (int i=0; i<points.size(); i++) {
		points[i].move(dx, dy);
	}

	firePoint.move(dx, dy);
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

void Polygon::addPoint(Point P) {
	points.push_back(P);
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

Point Polygon::getFirePoint() const {
	return firePoint;
}

Point Polygon::getTopLeftPosition() const {
	return topLeftPosition;
}

Point Polygon::getMostRightPoint() const {
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

Point Polygon::getMostLeftPoint() const {
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

Point Polygon::getMostBottomPoint() const {
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

Point Polygon::getMostUpperPoint() const {
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

int Polygon::getWidth() const {
	return getMostRightPoint().getAbsis() - getMostLeftPoint().getAbsis();
}
int Polygon::getHeight() const {
	return getMostBottomPoint().getAbsis() - getMostUpperPoint().getAbsis();
}
