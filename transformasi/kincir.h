#ifndef KINCIR_H
#define KINCIR_H

#include <cstdio>
#include <vector>
#include "../core/point.h"
#include "../core/canvas.h"
#include "../pattern/polygon.h"

class Kincir {
    public:
    Kincir(Canvas *p_canvas);
    Kincir(Canvas *p_canvas, Point center);
    Kincir(Canvas *p_canvas, int x, int y);
    Kincir(const Kincir&);
    const Kincir& operator= (const Kincir&);
    ~Kincir();

    void draw();
    void rotate(double radians);

    private:
    void init(Canvas *p_canvas);

    vector<Polygon> orig, transformed;
    Point center;
    double angle;

    static const double PI;
};

#endif
