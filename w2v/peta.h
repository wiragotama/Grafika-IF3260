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
		void showHighlightedArea(Canvas*);
		void moveHighlightedArea(char,Canvas*);
		OutCode ComputeOutCode(int x,int y);
		void CohenSutherlandLineClipAndDraw(Point p0, Point p1, Canvas*);
	
	private:
		void showSmallViewFrame(Canvas*);
		void loadFile(const char*);
		const int INSIDE; // 0000
		const int LEFT;   // 0001
		const int RIGHT;  // 0010
		const int BOTTOM; // 0100
		const int TOP;    // 1000

	private:
		vector<Polygon> islands;
		Polygon smallViewFrame;	
		
		/*******************************************/
		/*jangan lupa di refactor 2 atribut dibawah*/
		Point viewFrame[2];
		Polygon highlightedArea;
		int xmin, ymin, xmax, ymax;	
		/*******************************************/
};
#endif
