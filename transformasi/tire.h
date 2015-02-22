#ifndef TIRE_H
#define TIRE_H

#include "../core/header.h"
#include "../core/point.h"
#include "../core/circle.h"
#include "../core/canvas.h"

class Tire : public Circle {
	public :
		Tire(Point midPoint, int radius);
		~Tire();
		void bounce();
		void draw(Canvas *canvas, uint32_t color);
		int getBounceHeight();
		Point getBottomPosition();
		
	private :
		bool startBounce;
		int bounceHeight;
		bool bounceUp; //true untuk jalan ke atas, false untuk jalan ke bawah
};

#endif
