#ifndef PESAWAT_H
#define PESAWAT_H

#include <vector>
#include "animation.h"
#include "../core/canvas.h"
#include "../core/line.h"

class Pesawat : public Animation {
    public:
        Pesawat(Canvas* p_canvas);
        virtual void draw();
        virtual void update(double timeElapsed);
        virtual void setTopLeftPosition(Point p);

    private:
        std::vector<Line> lines;
        Canvas* p_canvas;
        static const double speed_x = .1;
};

#endif
