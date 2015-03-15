#include "../core/header.h"
#include "../core/graphicsio.h"
#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "../core/point.h"
#include "../pattern/polygon.h"
#include "../transformasi/helikopter.h"
#include "peta3d.h"

int main() {
	char c;
	Canvas canvas;
	GraphicsIO graphicsIO;
	Peta3D petaIndonesia;

	Polygon gambar;
	gambar.addPoint(Point(100,400));
	gambar.addPoint(Point(200,400));
	gambar.addPoint(Point(150,50));
	
	vector<Point> poly = gambar.getPoints();
	poly.push_back(poly[0]);

	Point line[2];
	line[0] = Point(50, 200);
	line[1] = Point(300, 200); 
	Line garis(line[0], line[1]);
	
	vector<Point> daftar;
	daftar.push_back(line[0]);
	daftar.push_back(line[1]);
	
	for(int i=0; i<poly.size()-1; i++) {
		if((Point::orientation(line[0], line[1], poly[i]) < 2 && Point::orientation(line[0], line[1], poly[i+1]) == 2) ||
		   (Point::orientation(line[0], line[1], poly[i]) == 2 && Point::orientation(line[0], line[1], poly[i+1]) < 2)){
			Line ltemp(poly[i], poly[i+1]);
			Point* p;
			p = garis.getIntersectionPointWith(ltemp);

			if (p) {
				daftar.push_back(*p);
				free(p);
			}
		}
	}
	
	printf("%d\n", daftar.size());
	
	sort(daftar.begin(), daftar.end(), Point::pointGreaterThan);
	
	vector<Line> peta3d;
	for(int i=0; i<daftar.size()-1; i++){
		if(! daftar[i].isEqual(daftar[i+1])){
			Point midPoint = Point((daftar[i].getAbsis()+ daftar[i+1].getAbsis())/2 , 
				(daftar[i].getOrdinat()+ daftar[i+1].getOrdinat())/2);
			//printf("Titik mid point: %d %d\n",midPoint.getAbsis(), midPoint.getOrdinat());
			// gambar.printInfo();
			if(!gambar.isPointInside(midPoint)) {
				// printf("bukan di dalam\n");
				peta3d.push_back(Line(daftar[i], daftar[i+1]));
			} else {
				// printf("di dalam\n");
			}
			// getchar();
		}
	}
	
	//for(int i=0; i<daftar.size(); i++){
	//	printf("%d %d\n", daftar[i].getAbsis(), daftar[i].getOrdinat());
	//}
	
	gambar.draw(&canvas, 0x00FFFFFF);
	for(int i=0; i<peta3d.size(); i++)
		peta3d[i].draw(&canvas, 1, 0x00FFFFFF);
		
	petaIndonesia.drawPeta3d(&canvas);
	
	canvas.flush();
		
	return 0;
}
