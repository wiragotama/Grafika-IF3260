#ifndef BODY_H
#define BODY_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/point.h"
#include "../core/line.h"
#include "../pattern/polygon.h"
#include "drawable.h"


#define colorRP 0
#define colorGP 255
#define colorBP 0

class Body {
	public:
		Body (Canvas *p_canvas);
		~Body();

		void draw();
        void move(int dx, int dy); //
        void setTopLeftPosition(Point p);
        Point getTopLeftPosition();
		void broke(); //
		
	private:
		Polygon polygons[2]; //klo pecah jadi 2, klo masih utuh hanya pake 1		
		bool broken;
		Point topLeftPosition;
};

#endif
