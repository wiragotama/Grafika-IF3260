#include "TerjunPayung.h"
int main() {
	Canvas canvas;
	vector<Point> p;
	Point topLeftPosition(100,100);
	p.push_back(Point(1,0));
	p.push_back(Point(10,0));
	TerjunPayung terjunPayung(&canvas, p, topLeftPosition);
	while (true) {
		terjunPayung.draw();
	}
	// return 0;
}