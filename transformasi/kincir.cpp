#include "kincir.h"

const double Kincir::PI = 3.141592654;

Kincir::Kincir() : center(400, 400) {
    angle = 0;
    init();
}

Kincir::Kincir(Point centerPoint) : center(centerPoint) {
	angle = 0;
	init();
}

Kincir::Kincir(int x, int y) {}
Kincir::Kincir(const Kincir& lonte) {}
const Kincir& Kincir::operator= (const Kincir& lonte) {}
Kincir::~Kincir() {}

vector<Polygon> Kincir::getPolygons() const {
    return transformed;
}

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
    for (vector<Polygon>::iterator it = transformed.begin(); it != transformed.end(); it++) {
        it->draw(canvas, color);
    }
}

void Kincir::init() {
    Point topLeft1(center.getAbsis(), center.getOrdinat()-10);
    Polygon baling1(topLeft1);
    baling1.loadPolygon(kincir1Path);
    baling1.loadPattern(kincirPattern);

    Point topLeft2(center.getAbsis(), center.getOrdinat());
    Polygon baling2(topLeft2);
    baling2.loadPolygon(kincir2Path);
    baling2.loadPattern(kincirPattern);

    Point topLeft3(center.getAbsis()-20, center.getOrdinat());
    Polygon baling3(topLeft3);
    baling3.loadPolygon(kincir3Path);
    baling3.loadPattern(kincirPattern);

    Point topLeft4(center.getAbsis() - 10, center.getOrdinat()-20);
    Polygon baling4(topLeft4);
    baling4.loadPolygon(kincir4Path);
    baling4.loadPattern(kincirPattern);

    orig.push_back(baling1);
    orig.push_back(baling2);
    orig.push_back(baling3);
    orig.push_back(baling4);
    transformed = orig;
}
