#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../core/point.h"

class Drawable {
	public:
		virtual void draw(Canvas *canvas, uint32_t color) = 0;
		
		virtual Point getTopLeftPosition() = 0;
		virtual void setTopLeftPosition(Point P) = 0;
		virtual void move(int dx, int dy) = 0;
		
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
				
		friend bool isCollide(const Drawable& a, const Drawable& b);
};

#endif
