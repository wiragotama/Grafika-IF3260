#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "canvas.h"
#include "../core/header.h"
#include <vector>
#include <cmath>

#define STRAIGHT_LINE 0
#define DASHED_LINE 1

typedef struct Pattern {
	vector<int> body;
	vector<int> thickness;
} Pattern;

class Line {
	public :
		Line(Point P1, Point P2);
		~Line();
		void initPatternList();

		Point getPointOne();
		Point getPointTwo();

		void setPointOne(Point P);
		void setPointTwo(Point P);

		void drawThickLine(Canvas *canvas, float thickness, uint32_t color);
		void drawStraightLine(Canvas *canvas, uint32_t color);
		void eraseStraightLine(Canvas *canvas);
		void eraseThickLine(Canvas *canvas, float thickness);
		
		/* Move on screen */
		void moveRight(int d);
		void moveLeft(int d);
		void moveUp(int d);
		void moveDown(int d);
		void moveRightDown(int dx, int dy);

	private :
		Point point[2];
		Pattern pattern;
		static const vector<Pattern> patternList;
};

#endif
