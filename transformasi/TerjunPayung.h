#ifndef TERJUNPAYUNG_H
#define TERJUNPAYUNG_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/point.h"
#include "../core/line.h"

class TerjunPayung {
	public:
		TerjunPayung(Canvas *canvas, vector<Point> points, Point topLeftPosition);
		~TerjunPayung();

		void move(int dx, int dy);
		void draw();

	private:
		vector<Point> points;
		Canvas *canvas;
		Point topLeftPosition;
};
#endif