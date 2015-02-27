#include "kincir.h"

const double Kincir::PI = 3.141592654;

Kincir::Kincir() : center(400, 400) {
    angle = 0;
    init();
}

Kincir::Kincir(Point center) {}
Kincir::Kincir(int x, int y) {}
Kincir::Kincir(const Kincir& lonte) {}
const Kincir& Kincir::operator= (const Kincir& lonte) {}
Kincir::~Kincir() {}

void Kincir::destroy() {
    if (orig.size() > 1)
        orig.erase(orig.begin()+1);
    if (transformed.size() > 1)
        transformed.erase(transformed.begin() + 1);
}

void Kincir::move(int dx, int dy) {
    for (int i = 0; i < orig.size(); ++i) {
        orig[i].move(dx, dy);
        transformed[i].move(dx, dy);
    }
    center.move(dx, dy);
}

void Kincir::rotate(double radians) {
    angle += radians;
    if (angle > 2 * PI) {
        angle -= 2 * PI;
    }
    for (int i = 0; i < orig.size(); ++i) {
        Point rot = orig[i].getPoint(0);
        transformed[i] = orig[i].rotate(angle, rot.getAbsis(), rot.getOrdinat());
    }
}

void Kincir::draw(Canvas *canvas, uint32_t color) {
    for (vector<Polygon>::iterator it = transformed.begin(); it != transformed.end(); it++)
        it->draw(canvas, color);
}

void Kincir::init() {
    Point topLeft1(center.getAbsis(), center.getOrdinat()-50);
    Polygon baling1(topLeft1);
    baling1.loadPolygon(kincir1Path);

    Point topLeft2(center.getAbsis(), center.getOrdinat());
    Polygon baling2(topLeft2);
    baling2.loadPolygon(kincir2Path);

    Point topLeft3(center.getAbsis()-100, center.getOrdinat());
    Polygon baling3(topLeft3);
    baling3.loadPolygon(kincir3Path);

    Point topLeft4(center.getAbsis() - 50, center.getOrdinat()-100);
    Polygon baling4(topLeft4);
    baling4.loadPolygon(kincir4Path);

    orig.push_back(baling1);
    orig.push_back(baling2);
    orig.push_back(baling3);
    orig.push_back(baling4);
    transformed = orig;
}
