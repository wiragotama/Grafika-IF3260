#ifndef GRAFIKA_MOUSE_H
#define GRAFIKA_MOUSE_H

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <pthread.h>
#include "mouse_listener.h"

#define MOUSEFILE "/dev/input/mice"

class Mouse {
	public:
	int getX() const;
	int getY() const;
	void setX(int);
	void setY(int);
	void setWindowHeight(int);
	void setWindowWidth(int);

	void registerListener(MouseListener*);

	void startListening();
	void stopListening();

	static Mouse& getInstance();

	const static int MOUSEFILE_OPEN_EXCEPTION = 1;

	private:
	/**
	 * Mouse should only be of one instance, so all of these methods are private.
	 * Constructors can throw MOUSEFILE_OPEN_EXCEPTION meaning MOUSEFILE can't be opened for some reason.
	 */
	Mouse();
	Mouse(const Mouse&);
	Mouse& operator= (const Mouse&);
	~Mouse();

	void mouseLoop();
	static void *mouseLoopHelper(void *context);

	pthread_t tid;
	MouseListener* mouseListener;
	/**
	 * coordinates of the mouse, using the scrseen coordinate.
	 * i.e. x grows to the left, y grows to the bottom
	 */
	int x, y, maxX, maxY;
	int windowHeight, windowWidth;

	int mouseFd;
	bool listening;

	static Mouse instance;
};

#endif
