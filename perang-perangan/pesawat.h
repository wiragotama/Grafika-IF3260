#ifndef PESAWAT_H
#define PESAWAT_H

#include <vector>
#include "animation.h"
#include "../core/canvas.h"
#include "../core/line.h"

#define colorRP 0
#define colorGP 255
#define colorBP 0

class Pesawat : public Animation {
    public:
        Pesawat(Canvas* p_canvas);
        virtual void draw();
        virtual void update(double timeElapsed);
        virtual void setTopLeftPosition(Point p);
        
        virtual void explode();
        virtual bool getFlag();
		Point fire();
		
    private:
        std::vector<Line> lines;
        Canvas* p_canvas;
        Point gun;
        int direction; //1 ke kanan, 2 ke kiri
        static const double speed_x = .1;
};

#endif
