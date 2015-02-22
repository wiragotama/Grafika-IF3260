#include "polygon.h"
#include "pattern.h"

int main() {
	Canvas canvas;
	Point topLeftPosition(100,100);
	
	Polygon polygon(&canvas, topLeftPosition);
	string polygonFile = "polygon.info"; //nama file jgn sampe salah ya... nanti kena segfault
	string patternFile = "ikan.info";
	
	polygon.loadPolygon(polygonFile.c_str());
	//printf("load polygon ok");
	polygon.loadPattern(patternFile.c_str());
	//printf("load burung ok");
	bool direction = true; //true = right, false = left
	while(true) {
		if (polygon.getMostLeftPoint().getAbsis()+polygon.getTopLeftPosition().getAbsis()<=2) {
			direction = true;
		}
		else if (polygon.getMostRightPoint().getAbsis()+polygon.getTopLeftPosition().getAbsis()>=canvas.get_vinfo().xres) {
			direction = false;
		}
		polygon.draw(canvas.pixel_color(255,0,0));
		if (direction)
			polygon.move(1,0);
		else 
			polygon.move(-1,0);
		canvas.flush();
	}
	return 0;
}
