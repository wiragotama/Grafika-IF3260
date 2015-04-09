#include "mouse.h"

// static stuffs here
Mouse Mouse::instance = Mouse();

Mouse& Mouse::getInstance() {
	return instance;
}

void* Mouse::mouseLoopHelper(void* context) {
	((Mouse *)context)->mouseLoop();
}
// end of static stuffs

Mouse::Mouse() {
	x = 0;
	y = 0;
	maxX = 640;
	maxY = 480;
	listening = false;

	if ((mouseFd = open(MOUSEFILE, O_RDONLY)) == -1) {
        throw MOUSEFILE_OPEN_EXCEPTION;
    }
}

Mouse::Mouse(const Mouse&) {
	// this should never me called
}

Mouse& Mouse::operator= (const Mouse&) {
	// this should never me called
}

Mouse::~Mouse() { // close the file
	close(mouseFd);
}

void Mouse::mouseLoop() {
	struct input_event ie;
	unsigned char button, bLeft, pLeft, bMiddle, pMiddle, bRight, pRight;
    char dx, px, dy, py;

	while(listening && read(mouseFd, &ie, sizeof(struct input_event))) {
		unsigned char *ptr = (unsigned char*)&ie;
		int i;

		button=ptr[0];
		bLeft = button & 0x1;
		bMiddle = ( button & 0x4 ) > 0;
        bRight = ( button & 0x2 ) > 0;
        dx=(char) ptr[1];
        dy=(char) ptr[2];

        // haven't accounted for first click
        if (bLeft && !pLeft)
			mouseListener->leftDown(x, y);
		if (!bLeft && pLeft)
			mouseListener->leftUp(x, y);
		if (bRight && !pRight)
			mouseListener->rightDown(x, y);
		if (!bRight && pRight)
			mouseListener->rightUp(x, y);
		if (bMiddle && !pMiddle)
			mouseListener->middleDown(x, y);
		if (!bMiddle && pMiddle)
			mouseListener->middleUp(x, y);

		x += dx;
		y -= dy;

		if (x < 0) x = 0;
		if (x >= maxX) x = maxX-1;
		if (y < 0) y = 0;
		if (y >= maxY) y = maxY-1;

		if (x != px || y != py)
			mouseListener->movement(x, y);

		pLeft = bLeft;
		pRight = bRight;
		pMiddle = bMiddle;
		px = x;
		py = y;
	}
}

void Mouse::registerListener(MouseListener* mMouseListener) {
	mouseListener = mMouseListener;
}

void Mouse::startListening() {
	listening = true;
	pthread_create(&tid, NULL, &Mouse::mouseLoopHelper, this);
}

void Mouse::stopListening() {
	listening = false;
	pthread_join(tid, NULL);
	delete mouseListener;
}

int Mouse::getX() const {
	return x;
}

int Mouse::getY() const {
	return y;
}

void Mouse::setX(int mx) {
	x = mx;
}

void Mouse::setY(int my) {
	y = my;
}

void Mouse::setWindowHeight(int height) {
	windowHeight = height;
}

void Mouse::setWindowWidth(int width) {
	windowWidth = width;
}

