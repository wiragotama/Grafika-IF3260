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
        virtual void update(time_t timeElapsed);

    private:
        std::vector<Line> lines;
        Canvas* p_canvas;
};

#endif
