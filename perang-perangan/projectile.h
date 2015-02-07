#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <vector>
#include "animation.h"
#include "../core/canvas.h"
#include "../core/line.h"

#define projectileR 0
#define projectileG 0
#define projectileB 255

class Projectile : public Animation {
	public :
		Projectile(Canvas *canvas, int direction);
		~Projectile();
		virtual void draw();
        virtual void update(double timeElapsed);
        virtual void setTopLeftPosition(Point p);
        
        virtual void explode();
        virtual bool getFlag();
        
	private :
		Line line;
		float thickness;
        Canvas* p_canvas;
        int direction; //1 up, 2 down
        static const double speed_x = .1;
        bool flag; //ni buat resolve masalah segmentation fault pas projectile dah nyampe ujung layar. flag=true pas nyampe di ujung layar
};

#endif
