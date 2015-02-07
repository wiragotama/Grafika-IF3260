#ifndef KAPAL_H
#define KAPAL_H

#include <vector>
#include "animation.h"
#include "../core/canvas.h"
#include "../core/line.h"

class Kapal : public Animation {
    public:
        Kapal(Canvas* p_canvas);
        virtual void draw();
        virtual void update(double timeElapsed);
        virtual void setTopLeftPosition(Point p);
		void fire();

    private:
        std::vector<Line> lines;
        Point gun;
        Canvas* p_canvas;
        static const double speed_x = .1;
};

#endif
