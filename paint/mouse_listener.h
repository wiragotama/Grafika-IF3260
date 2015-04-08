#ifndef GRAFIKA_MOUSE_LISTENER_H
#define GRAFIKA_MOUSE_LISTENER_H

class MouseListener {
	public:
	MouseListener();
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
};

#endif
