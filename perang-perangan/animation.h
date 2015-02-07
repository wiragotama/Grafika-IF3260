#ifndef ANIMATION_H
#define ANIMATION_H

#include "../core/point.h"
#include "../core/header.h"
#include <ctime>

class Animation {
	public:
		virtual void draw() = 0;
		virtual void update(double timeElapsed) = 0;
		void setTopLeftPosition(int x, int y);
		virtual void setTopLeftPosition(Point p);
		void setWidth(int width);
		void setHeight(int height);
		int getWidth();
		int getHeight();
		Point getTopLeftPosition() const;
		Point getBottomRight() const;
		bool isCollide(const Animation& other);
		
		virtual void explode() = 0;
		virtual bool getFlag() = 0; //khusus utk projectile, flag=true klo nyampe di ujung layar

	private:
		int width, height;
		Point topLeftPosition;
};

#endif
