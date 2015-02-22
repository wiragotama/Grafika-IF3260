#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../core/point.h"

class Drawable {
	public:
		virtual void draw() = 0;
		
		virtual Point getTopLeftPosition() const = 0;
		virtual void setTopLeftPosition() = 0;
		virtual void move(int dx, int dy) = 0;
		
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
				
		friend bool isCollide(const Drawable& a, const Drawable& b);
};

#endif
