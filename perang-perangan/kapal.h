#ifndef KAPAL_H
#define KAPAL_H

#include <vector>
#include "animation.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "../core/header.h"

#define colorRK 255
#define colorGK 0
#define colorBK 0

class Kapal : public Animation {
    public:
        Kapal(Canvas* p_canvas);
        virtual void draw();
        virtual void update(double timeElapsed);
        virtual void setTopLeftPosition(Point p);
        
        virtual void explode();
        virtual bool getFlag();
		Point fire();
		
    private:
        std::vector<Line> lines;
        Point gun;
        int direction; //1 ke kanan, 2 ke kiri
        Canvas* p_canvas;
        static const double speed_x = .1;
};

#endif
