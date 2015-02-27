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
		void zoomIn(); //todo
		void zoomOut(); //todo
		OutCode ComputeOutCode(int x,int y);
		void CohenSutherlandLineClipAndDraw(Point p0, Point p1, Canvas*);
	private:
		void show_s_view_frame(Canvas*);
		void loadFile(const char*);
		const int INSIDE; // 0000
		const int LEFT;   // 0001
		const int RIGHT;  // 0010
		const int BOTTOM; // 0100
		const int TOP;    // 1000

	private:
		vector<Polygon> islands;
		// int size_width; ini untuk apa ya?
		// int size_height;
		
		/*******************************************/
		/*jangan lupa di refactor 2 atribut dibawah*/
		Point viewFrame[2];
		int xmin, ymin, xmax, ymax;	
		/*******************************************/
};
#endif
