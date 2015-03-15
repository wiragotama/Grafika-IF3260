#include "../pattern/polygon.h"

const int MAXINT = 0x7FFFFFFF;

Polygon::Polygon() {
    init();
}

Polygon::Polygon(Point topLeftPosition) {
    init();
	this->topLeftPosition = topLeftPosition;
}

Polygon::Polygon(Point topLeftPosition, vector<Point> nodes, Point firePoint, Pattern pattern_t) : pattern(pattern_t) {
    init();
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
    init();
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

void Polygon::init() {
	min_x = max_x = min_y = max_y = -1;
}

int Polygon::getMaxY() const {
    // if (max_y == -1) { // haven't computed yet
        vector<Point>::const_iterator it = points.begin();
        // it must have at least a point right?
        max_y = it->getOrdinat(); it++;

        while (it != points.end()) {
            int y = it->getOrdinat();
            if (y > max_y)
                max_y = y;
            it++;
        }
    // }
    return max_y + topLeftPosition.getOrdinat();
}

int Polygon::getMinY() const {
    // if (min_y == -1) { // haven't computed yet
        vector<Point>::const_iterator it = points.begin();
        // it must have at least a point right?
        min_y = it->getOrdinat(); it++;

        while (it != points.end()) {
            int y = it->getOrdinat();
            if (y < min_y)
                min_y = y;
            it++;
        }
    // }
    return min_y + topLeftPosition.getOrdinat();
}

int Polygon::getMinX() const {
    // if (min_x == -1) { // haven't computed yet
        vector<Point>::const_iterator it = points.begin();
        // it must have at least a point right?
        min_x = it->getAbsis(); it++;

        while (it != points.end()) {
            int x = it->getAbsis();
            if (x < min_x)
                min_x = x;
            it++;
        }
    // }
    return min_x + topLeftPosition.getAbsis();
}

int Polygon::getMaxX() const {
    // if (max_x == -1) { // haven't computed yet
        vector<Point>::const_iterator it = points.begin();
        // it must have at least a point right?
        max_x = it->getAbsis(); it++;

        while (it != points.end()) {
            int x = it->getAbsis();
            if (x > max_x)
                max_x = x;
            it++;
        }
    // }
    return max_x + topLeftPosition.getAbsis();
}

Point Polygon::getOriginFirePoint() const {
	return originFirePoint;
}

vector<Point> Polygon::getPoints() const {
	return points;
}

vector<Line> Polygon::getLines() const {
	vector<Point> tempPoints = getPoints();
	vector<Line> polygonLines;
	if(tempPoints.size()>0)
		tempPoints.push_back(tempPoints[0]);
	for(int i=0; i<tempPoints.size()-1; i++){
		polygonLines.push_back( Line(tempPoints[i], tempPoints[i+1]) );
	}
	return polygonLines;
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
    printf("\ntopleftPosition");
    topLeftPosition.printInfo();
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
	// printf("ini %d %d\n",topLeftPosition.getAbsis(),topLeftPosition.getOrdinat());
	// getchar();
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
		floodFill(canvas, firePoint.getAbsis(), firePoint.getOrdinat(), color);

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
		floodFillBackground(canvas, firePoint.getAbsis(), firePoint.getOrdinat(), color);
}

void Polygon::floodFill(Canvas* canvas, int x, int y, uint32_t color) {
	long location = canvas->getCursorLocation(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat());
	int dx = originFirePoint.getAbsis()-firePoint.getAbsis(), dy = originFirePoint.getOrdinat()-firePoint.getOrdinat();

	int screen_x = x + topLeftPosition.getAbsis();
	int screen_y = y + topLeftPosition.getOrdinat();

	if ((screen_x>=0 && screen_x<canvas->get_vinfo().xres) && (screen_y>=0 && screen_y<canvas->get_vinfo().yres) && (canvas->getColor(location) >>24!=0xff)) {
		if (getColor(x+dx, y+dy)!=0)
			canvas->putPixelColor(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat(), color);
		else 
			canvas->putPixelColor(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat(), getColor(x+dx, y+dy));
		floodFill(canvas, x-1, y, color);
		floodFill(canvas, x+1, y, color);
		floodFill(canvas, x, y-1, color);
		floodFill(canvas, x, y+1, color);
	}
}

void Polygon::floodFillBackground(Canvas* canvas, int x, int y, uint32_t color) {
	long location = canvas->getCursorLocation(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat());
	int dx = originFirePoint.getAbsis()-firePoint.getAbsis(), dy = originFirePoint.getOrdinat()-firePoint.getOrdinat();

	int screen_x = x + topLeftPosition.getAbsis();
	int screen_y = y + topLeftPosition.getOrdinat();

	if ((screen_x>=0 && screen_x<canvas->get_vinfo().xres) && (screen_y>=0 && screen_y<canvas->get_vinfo().yres)) {
		if (getColor(x+dx, y+dy)!=0)
			canvas->putPixelColor(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat(), color);
		else 
			canvas->putPixelColor(x+topLeftPosition.getAbsis(), y+topLeftPosition.getOrdinat(), getColor(x+dx, y+dy));
		floodFillBackground(canvas, x-1, y, color);
		floodFillBackground(canvas, x+1, y, color);
		floodFillBackground(canvas, x, y-1, color);
		floodFillBackground(canvas, x, y+1, color);
	}
}

void Polygon::move(int dx, int dy) {
	//firePoint.move(dx, dy);
	topLeftPosition.move(dx, dy);
}

void Polygon::loadPolygon(const char* filename) {
	int numPoints, x, y;
	FILE *matrix_file;
	matrix_file = fopen(filename,"r");

	fscanf(matrix_file, "%d", &numPoints);

	int max_x, min_x, max_y, min_y;
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

void Polygon::setTopLeftPosition(Point p) {
	topLeftPosition = p;
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
	return getMostBottomPoint().getOrdinat() - getMostUpperPoint().getOrdinat();
}

Polygon Polygon::resizing(double scale, int pivot_x, int pivot_y){
	vector<Point> transformed = points;
	transformed.push_back(Point(0, 0));
     
    // Pindahkan titik tengah ke point(0,0);
    for (vector<Point>::iterator it = transformed.begin(); it != transformed.end(); it++) {
    int awal_x = it->getAbsis();
    int awal_y = it->getOrdinat();
    it->setAbsis(awal_x - pivot_x);
    it->setOrdinat(awal_y - pivot_y);
    }
     
    // transformasi ubah ukuran
    for (vector<Point>::iterator it = transformed.begin(); it != transformed.end(); it++) {
    int awal_x = it->getAbsis();
    int awal_y = it->getOrdinat();
    it->setAbsis((int) (awal_x * scale));
    it->setOrdinat((int) (awal_y *scale));
    }
     
     
    //Kembalikan ke posisi semula
    for (vector<Point>::iterator it = transformed.begin(); it != transformed.end(); it++) {
		int awal_x = it->getAbsis();
		int awal_y = it->getOrdinat();
		it->setAbsis((int) (awal_x + pivot_x));
		it->setOrdinat((int) (awal_y + pivot_y));
    }
     
    //Ambil kembali firepoint dan topleftposition
    Point newTopLeft = transformed[transformed.size()-1];
	int dx = newTopLeft.getAbsis();
	int dy = newTopLeft.getOrdinat();
	newTopLeft.setAbsis(newTopLeft.getAbsis() + topLeftPosition.getAbsis());
	newTopLeft.setOrdinat(newTopLeft.getOrdinat() + topLeftPosition.getOrdinat());
	transformed.pop_back();
	for (vector<Point>::iterator it = transformed.begin() ;it != transformed.end(); ++it) {
		it->setAbsis(it->getAbsis() - dx);
		it->setOrdinat(it->getOrdinat() - dy); 
	}
	return Polygon(newTopLeft, transformed, firePoint, pattern);
}

bool Polygon::sortTopLeft(const Polygon& lhs, const Polygon& rhs) {
	Point TLP = Point(lhs.getMinX(), lhs.getMinY());
	Point TLP2 = Point(rhs.getMinX(), rhs.getMinY());
	
	if (TLP.getAbsis() == TLP2.getAbsis()) {
		return (TLP.getOrdinat() < TLP2.getOrdinat());
	}
	else return (TLP.getAbsis() < TLP2.getAbsis());
}

Point Polygon::getBottomRightPoint() const {
	return Point(getMostRightPoint().getAbsis(), getMostBottomPoint().getOrdinat());
}

Point Polygon::getSuitableFirePoint(Canvas* canvas) {
	//left for winson
	return Point(0,0);
}

void Polygon::simulateFloodFill(int x, int y, uint32_t** matrix, Point TLP, Point BRP) {
	
	if ((x>=TLP.getAbsis() && x<=BRP.getAbsis()) && (y>=TLP.getOrdinat() && y<=BRP.getOrdinat()) && 
		(matrix[y][x]==0)	
	) {
		matrix[y][x] = 2345678;
		simulateFloodFill(x-1, y, matrix, TLP, BRP);
		simulateFloodFill(x+1, y, matrix, TLP, BRP);
		simulateFloodFill(x, y-1, matrix, TLP, BRP);
		simulateFloodFill(x, y+1, matrix, TLP, BRP);
	}
}
bool Polygon::isPointInside(Point point) const {
	vector<Point> edges = this->getPoints();
	if(edges.size()>0)
		edges.push_back(edges[0]);
	double sum = 0;
	for (int p = 0; p < edges.size()-1; ++p){
		float temp = 0.0f;
		if (Point::ccw(edges[p], edges[p+1], point)) {
			temp = Line::angle(edges[p], point, edges[p+1]);
			sum += temp;
			// printf("%s\n", "ccw");
		} else {
			temp -= Line::angle(edges[p], point, edges[p+1]);
			sum -= temp;
			// printf("%s\n", "cw");
		}
		// edges[p].printInfo();edges[p+1].printInfo();point.printInfo();
		// printf("nilai sudut %f ",temp*180/M_PI);
	}
	// printf("\n%lf\n", fabs(fabs(sum) - 2*M_PI));
	bool inPolygon = (fabs(fabs(sum) - 2*M_PI) < 0.000001);
	return inPolygon;
}

