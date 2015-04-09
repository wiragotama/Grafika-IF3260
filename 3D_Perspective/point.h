#ifndef _POINT_H
#define _POINT_H
#include "canvas.h"

class Point {
	public :
		Point();
		Point(double new_x, double new_y); 
		//Default copy constructor, destructor, assignment
		
		double getAbsis() const;
		double getOrdinat() const;
		void setAbsis(double x);
		void setOrdinat(double y);
		
		void draw(Canvas *canvas, uint32_t color);
		void drawPersistent(Canvas *canvas, uint32_t color);
		
		bool operator==(const Point p) const;
		
	private :
		double x;
		double y;
};

#endif
