#ifndef GRAFIKA_MOUSE_LISTENER_H
#define GRAFIKA_MOUSE_LISTENER_H
#include "../3D_Perspective/canvas.h"
#include "../3D_Perspective/point.h"
#include "../3D_Perspective/line.h"
#include "../3D_Perspective/polygon.h"
class MouseListener {
	public:

	MouseListener(Canvas*);
	MouseListener(const MouseListener&);
	MouseListener& operator= (const MouseListener&);
	virtual ~MouseListener();

	virtual void leftDown(int, int);
	virtual void leftUp(int, int);
	virtual void rightDown(int, int);
	virtual void rightUp(int, int);
	virtual void middleDown(int, int);
	virtual void middleUp(int, int);
	virtual void movement(int, int);

	public:
		Canvas *canvas;
};

#endif
