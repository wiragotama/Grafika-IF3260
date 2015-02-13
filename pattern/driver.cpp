#include "polygon.h"
#include "pattern.h"

int main() {
	Canvas canvas;
	Point topLeftPosition(100,100);
	
	Polygon polygon(&canvas, topLeftPosition);
	string polygonFile = "polygon.info"; //nama file jgn sampe salah ya... nanti kena segfault
	string patternFile = "pattern.info";
	
	polygon.loadPolygon(polygonFile.c_str());
	polygon.loadPattern(patternFile.c_str());
	printf("load ok\n");
	polygon.draw();
	return 0;
}
