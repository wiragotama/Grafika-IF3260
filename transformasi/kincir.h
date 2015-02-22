#ifndef KINCIR_H
#define KINCIR_H

#include <vector>
#include "../core/point.h"

class Kincir {
    public:
    Kincir();
    Kincir(Point center);
    Kincir(int x, int y);
    Kincir(const Kincir&);
    const Kincir& operator= (const Kincir&);
    ~Kincir();

    private:
    void init(Canvas *p_canvas);

    vector<Polygon> orig;
    Point center;
};

#endif
