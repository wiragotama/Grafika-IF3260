#ifndef helikopter_H
#define helikopter_H

#include "../transformasi/body.h"
#include "../transformasi/tire.h"
#include "../transformasi/drawable.h"
#include "../core/point.h"
#include "../core/line.h"
#include "../core/canvas.h"
#include "../core/header.h"
#include "../pattern/polygon.h"

class Helikopter : public Drawable {
	public :
		Helikopter(Canvas *p_canvas, Point topLeftPosition);
		~Helikopter();
		
		Point getTopLeftPosition();
		void setTopLeftPosition(Point P);
		void move(int dx, int dy);
		
		int getWidth();
		int getHeight();
		
		void brokeBody();
		void bounceTire();
		
		Tire getTire();
		Body getBody();
		
		void draw(uint32_t color);
		bool atBottomOfScreen();
		
	private :
		Body body;
		Tire tire;
		Canvas *canvas;
		//baling2
		Point topLeftPosition;
};

#endif
