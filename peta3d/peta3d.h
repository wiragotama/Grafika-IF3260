#ifndef PETA3D_H
#define PETA3D_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "../core/point.h"
#include "../pattern/polygon.h"
#include "../transformasi/helikopter.h"
#include <vector>
#include <algorithm>

class Peta3D {
public:
	Peta3D();
	void drawPeta(Canvas*);
	void drawPeta3d(Canvas* canvas);
	void move(int, int);
	
private:
	void loadPeta2d(const char*);
	vector<Polygon> polygonTo3D(Polygon*, int);
	void generetePeta3dSurfaces();
	void generetePeta3dFromSurface();
	
private:
	vector<Polygon> peta2d;
	vector<Polygon> petaSurface;
	vector<Line> peta3d;
	int relativePositionX;
	int relativePositionY;
};
#endif
