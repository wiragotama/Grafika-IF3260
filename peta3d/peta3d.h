#ifndef PETA3D_H
#define PETA3D_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "../core/point.h"
#include "../pattern/polygon.h"
#include "../transformasi/helikopter.h"

class Peta3D {
public:
	Peta3D();
	void drawPeta(Canvas);
	void loadPeta2d(const char*);
	
private:
	vector<Polygon> peta2d;
	vector<Polygon> petaSurface;
	vector<Line> peta3d;
};
#endif