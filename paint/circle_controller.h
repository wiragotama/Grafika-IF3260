#ifndef CIRCLE_CONTROLLER_H
#define CIRCLE_CONTROLLER_H

#include "mouse_listener.h"
#include <iostream>
#include "../3D_Perspective/canvas.h"
#include "../3D_Perspective/line.h"
#include "../3D_Perspective/polygon.h"
#include "../3D_Perspective/circle.h"
class CircleController : public MouseListener {
	public:
	CircleController(Canvas*);
	CircleController(const CircleController&);
	CircleController& operator= (const CircleController&);
	virtual ~CircleController();

	virtual void leftDown(int, int);
	virtual void leftUp(int, int);
	virtual void movement(int, int);

	private:
	void drawCircle(int);
	// void drawLineTerhadapPusat(Point);

	Polygon* poly;
	bool dragged;
	Point center;

};

#endif
