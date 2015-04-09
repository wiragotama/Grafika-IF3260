#ifndef POLYGON_CONTROLLER_H
#define POLYGON_CONTROLLER_H

#include "mouse_listener.h"
#include <iostream>
#include "../3D_Perspective/canvas.h"
#include "../3D_Perspective/line.h"
#include "../3D_Perspective/polygon.h"

class PolygonController : public MouseListener {
	public:
	PolygonController(Canvas*);
	PolygonController(const PolygonController&);
	PolygonController& operator= (const PolygonController&);
	virtual ~PolygonController();

	virtual void leftDown(int, int);
	virtual void leftUp(int, int);
	virtual void rightDown(int, int);
	virtual void movement(int, int);

	private:
	vector<Point> point;

};

#endif
