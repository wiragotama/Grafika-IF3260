#ifndef GRAFIKA_RECTANGLE_CONTROLLER_H
#define GRAFIKA_RECTANGLE_CONTROLLER_H

#include "mouse_listener.h"
#include <iostream>

class RectangleController : public MouseListener {
	public:
	RectangleController();
	RectangleController(const RectangleController&);
	RectangleController& operator= (const RectangleController&);
	virtual ~RectangleController();

	virtual void leftDown(int, int);
	virtual void leftUp(int, int);
	virtual void movement(int, int);

	private:
	int leftX, topY, width, height;
	bool dragged;
};

#endif
