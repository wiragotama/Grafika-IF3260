#include "kincir.h"

Kincir::Kincir() {
    
}

Kincir::Kincir(Point center);
Kincir::Kincir(int x, int y);
Kincir::Kincir(const Kincir&);
const Kincir& Kincir::operator= (const Kincir&);
Kincir::~Kincir();

void Kincir::init(Canvas *p_canvas) {
    Point topLeft(400, 400);
    Polygon baling1(p_canvas, topLeft);
    baling.loadPolygon("kincir1.info");
    baling.loadPattern("yellow.info");
    orig.pushBack();
    orig.pushBack();
    orig.pushBack();
    orig.pushBack();
:pwd
}
