#ifndef TRIANGLE_CONTROLLER_H
#define TRIANGLE_CONTROLLER_H

#include "mouse_listener.h"
#include <iostream>
#include "../3D_Perspective/canvas.h"
#include "../3D_Perspective/line.h"
#include "../3D_Perspective/polygon.h"
class TriangleController : public MouseListener {
	public:
	TriangleController(Canvas*);
	TriangleController(const TriangleController&);
	TriangleController& operator= (const TriangleController&);
	virtual ~TriangleController();

	virtual void leftDown(int, int);
	virtual void leftUp(int, int);
	virtual void movement(int, int);

	private:
	void drawTriangle();
	Polygon* poly;
	int state;
	Point point[3];
	// vector<Point> point;

};

#endif
