#ifndef GRAFIKA_MOUSE_LISTENER_H
#define GRAFIKA_MOUSE_LISTENER_H
#include "../core/canvas.h"
#include "../core/line.h"
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
