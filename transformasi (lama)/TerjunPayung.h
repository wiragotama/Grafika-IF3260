#ifndef TERJUNPAYUNG_H
#define TERJUNPAYUNG_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/point.h"
#include "../core/line.h"
#include "../core/circle.h"

class TerjunPayung {
	public:
		TerjunPayung (Canvas *canvas, Point topLeftPosition);
		~TerjunPayung();

		void moveDown(int);
		void draw();

	private:
		vector<Line> lines;
		Canvas *canvas;
		Circle head;
		Circle parachute;
		Point topLeftPosition;
};

#endif