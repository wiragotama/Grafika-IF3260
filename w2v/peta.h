#ifndef PETA_H
#define PETA_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "../core/point.h"
#include "../pattern/polygon.h"
#include "../transformasi/helikopter.h"

typedef int OutCode;

class Peta {
	public:
		Peta();
		~Peta();
		void drawIndonesia(Canvas*);
		void drawKapal(Canvas*);
		void moveKapal();
        void drawHeli(Canvas*);
		void zoomIn();
		void zoomOut();
		void showHighlightedArea(Canvas*);
		void moveHighlightedArea(char);

	private:
		OutCode ComputeOutCode(int x,int y, int, int, int, int);
		void CohenSutherlandLineClipAndDraw(Point p0, Point p1, Canvas*);
		void drawViewFrame(Canvas*);
		void loadFile(const char*);
		void scaleAndDraw(Canvas*, Point p0, Point p1);
		void initialzeKapal();
		const int INSIDE; // 0000
		const int LEFT;   // 0001
		const int RIGHT;  // 0010
		const int BOTTOM; // 0100
		const int TOP;    // 1000

	private:
		vector<Polygon> islands;
		Polygon viewFrame;
		Polygon highlightedArea;
        Helikopter heli;

        int dx_heli;
		Polygon kapal;
		Polygon layarKapal;
		bool arahKapal;
};
#endif
