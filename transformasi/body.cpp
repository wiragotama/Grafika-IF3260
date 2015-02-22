Body::Body (Canvas *p_canvas) : polygon[0](p_canvas,Point(0,0)), polygon[1](p_canvas, Point(0,0)) {
	broken = false;
	topLeftPosition = Point(0,0);
}

Body::~Body() {
}

void Body::draw() {
	polygon[0].draw();
	if (broken) 
		polygon[1].draw();
}

void Body::move(int dx, int dy) {
	polygon[0].move(dx,dy);
	if(broken)
		polygon[1].move(dx,dy);
}

void Body::setTopLeftPosition(Point p) {
	polygon[0].setTopLeftPosition(p.getAbsis(),p.getOrdinat());
	if(broken)
		polygon[1].setTopLeftPosition(p.getAbsis()+250,p.getOrdinat());
}

void Body::broke(const char* filename1, const char* filename2, const char* pattern) {
	broken = true;
	polygon[0].loadPolygon(filename1);
	polygon[0].loadPattern(pattern);
	polygon[1].loadPolygon(filename2);
	polygon[1].loadPattern(pattern);
}
