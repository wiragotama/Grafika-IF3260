#ifndef TIRE_H
#define TIRE_H

#include "../core/header.h"
#include "../core/point.h"
#include "../core/circle.h"
#include "../core/canvas.h"
#include "drawable.h"

class Tire : public Drawable {
	public :
		Tire(Point centerPoint, int radius);
		~Tire();
		void draw();
		void move(int dx, int dy);
		void bounce();
		void setPosition();
		void setColor(uint32_t color);
		uint32_t getColor();
		Point getCenterPoint();
		Point getBottomPosition();
		Point getTopPosition();
		int getHeight(); //bounce height
		int getWidth(); //tire diameter
		
	private :
		Point centerPoint;
		Point bottomPosition;
		Point topPosition;
		int radius;
		int bounceHeight;
		Canvas *canvas;
		uint32_t color;

};

#endif
