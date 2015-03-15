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

typedef int OutCode;

class Peta3D {
public:
	Peta3D();
	void drawPeta(Canvas*);
	void drawPeta3d(Canvas* canvas);
	void drawPetaClipping(Canvas* canvas);
	void move(int, int);
	void zoomOut();
	void zoomIn();
private:
	void loadPeta2d(const char*);
	vector<Polygon> polygonTo3D(Polygon*, int);
	void generetePeta3dSurfaces();
	void generetePeta3dFromSurface();
	void CohenSutherlandLineClipAndDraw(Point p0, Point p1, Canvas* canvas);
	OutCode ComputeOutCode(int x, int y, int xmin, int ymin, int xmax, int ymax);
	void scaleAndDraw(Canvas* canvas, Point p0, Point p1);

private:
	vector<Polygon> peta2d;
	vector<Polygon> petaSurface;
	vector<Line> peta3d;
	Polygon viewFrame;
	Polygon highlightedArea;
	const int INSIDE; // 0000
	const int LEFT;   // 0001
	const int RIGHT;  // 0010
	const int BOTTOM; // 0100
	const int TOP;    // 1000
	int relativePositionX;
	int relativePositionY;
};
#endif
