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
#include "../transformasi/kincir.h"

class Helikopter : public Drawable {
	public :
		Helikopter(Point topLeftPosition);
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
        vector<Polygon> getAllPolygons() const;
		
		void draw(Canvas *canvas, uint32_t color);
		bool atBottomOfScreen(int yres);
		void kincirDestroy();
		
	private :
		Body body;
		Tire tire;
		Kincir kincir;
		Point topLeftPosition;
};

#endif
