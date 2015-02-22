#include "kincir.h"

const double Kincir::PI = 3.141592654;

Kincir::Kincir(Canvas *p_canvas) : center(400, 400) {
    angle = 0;
    init(p_canvas);
}

Kincir::Kincir(Canvas *p_canvas, Point center) {}
Kincir::Kincir(Canvas *p_canvas, int x, int y) {}
Kincir::Kincir(const Kincir& lonte) {}
const Kincir& Kincir::operator= (const Kincir& lonte) {}
Kincir::~Kincir() {}

void Kincir::rotate(double radians) {
    angle += radians;
    if (angle > 2 * PI) {
        angle -= 2 * PI;
    }
    for (int i = 0; i < 4; ++i) {
        Point rot = orig[i].getPoint(0);
        transformed[i] = orig[i].rotate(angle, rot.getAbsis(), rot.getOrdinat());
    }
}

void Kincir::draw() {
    for (vector<Polygon>::iterator it = transformed.begin(); it != transformed.end(); it++)
        it->draw(0x00FFFF);
}

void Kincir::init(Canvas *p_canvas) {
    printf("Kincir::init\n");

    Point topLeft1(center.getAbsis(), center.getOrdinat()-50);
    Polygon baling1(p_canvas, topLeft1);
    baling1.loadPolygon("kincir1.info");

    Point topLeft2(center.getAbsis(), center.getOrdinat());
    Polygon baling2(p_canvas, topLeft2);
    baling2.loadPolygon("kincir2.info");

    Point topLeft3(center.getAbsis()-100, center.getOrdinat());
    Polygon baling3(p_canvas, topLeft3);
    baling3.loadPolygon("kincir3.info");

    Point topLeft4(center.getAbsis() - 50, center.getOrdinat()-100);
    Polygon baling4(p_canvas, topLeft4);
    baling4.loadPolygon("kincir4.info");

    orig.push_back(baling1);
    orig.push_back(baling2);
    orig.push_back(baling3);
    orig.push_back(baling4);
    transformed = orig;
}
