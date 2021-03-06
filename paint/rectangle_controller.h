#ifndef GRAFIKA_RECTANGLE_CONTROLLER_H
#define GRAFIKA_RECTANGLE_CONTROLLER_H

#include "mouse_listener.h"
#include <iostream>
#include "../3D_Perspective/canvas.h"
#include "../3D_Perspective/line.h"
#include "../3D_Perspective/polygon.h"
class RectangleController : public MouseListener {
	public:
	RectangleController(Canvas*);
	RectangleController(const RectangleController&);
	RectangleController& operator= (const RectangleController&);
	virtual ~RectangleController();

	virtual void leftDown(int, int);
	virtual void leftUp(int, int);
	virtual void movement(int, int);

	private:
	void drawRectangle(int, int, int, int);

	Polygon* poly;
	int leftX, topY, width, height;
	bool dragged;

};

#endif
