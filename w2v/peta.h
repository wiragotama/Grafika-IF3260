#ifndef PETA_H
#define PETA_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "../core/point.h"
#include "../pattern/polygon.h"

typedef int OutCode;

class Peta {
	public:
		Peta();
		~Peta();
		void windowToView(Canvas*);
		void zoomIn();
		void zoomOut();
		OutCode ComputeOutCode(int x,int y);
		void CohenSutherlandLineClipAndDraw(Point p0, Point p1, Canvas*);
	private:
		void loadFile(const char*);

	public:
		const int INSIDE; // 0000
		const int LEFT;   // 0001
		const int RIGHT;  // 0010
		const int BOTTOM; // 0100
		const int TOP;    // 1000

	private:
		vector<Polygon> islands;
		Point viewFrame[2];
		int size_width;
		int size_height;
		int xmin, ymin, xmax, ymax;
	
};
#endif
