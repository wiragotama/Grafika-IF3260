#include "circle.h"

Circle::Circle(double x, double y, double radius){
	a = x;
	b = y;
	r = radius;
}
		
void Circle::drawfill(Canvas *canvas, uint32_t color){
	int ri = ceil(r);
	int bi = round(b);
	
	for (int y= bi-ri; y<= bi+ri; y++){
		double determinan = r*r - (y-b)*(y-b) ;
		if (determinan > 0){
			double dy = sqrt(determinan);
			double x1 = a - dy;
			double x2 = a + dy;
			Line line( Point(x1,y), Point(x2,y));
			line.draw(canvas, 1, color);
		}
	}
}
