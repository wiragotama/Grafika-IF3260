#ifndef BODY_H
#define BODY_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/point.h"
#include "../core/line.h"
#include "../pattern/polygon.h"
#include <vector>

#define colorRP 0
#define colorGP 255
#define colorBP 0

class Body {
	public:
		Body(Canvas *p_canvas, Point topLeftPosition);
		~Body();
		
		void draw(uint32_t);
		void move(int dx, int dy);
		void broke();
		void setTopLeftPosition(Point topLeftPosition);
		Point getTopLeftPosition();
		
		int getWidth();
		int getHeight();
		
	private :
		vector<Polygon> polygons;
		bool broken;
		Point topLeftPosition;
};

#endif
