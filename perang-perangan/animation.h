#ifndef ANIMATION_H
#define ANIMATION_H

#include "../core/point.h"
#include <ctime>

class Animation {
	public:
		virtual void draw() = 0;
		virtual void update(double timeElapsed) = 0;
		void setTopLeftPosition(int x, int y);
		void setTopLeftPosition(Point p);
		void setWidth(int width);
		void setHeight(int height);
		Point getTopLeftPosition() const;
		Point getBottomRight() const;
		bool isCollide(const Animation& other);

	private:
		int width, height;
		Point topLeftPosition;
};

#endif
