#include "graphicsio.h"

GraphicsIO::GraphicsIO() {}

GraphicsIO::~GraphicsIO() {}

void GraphicsIO::initTermios(int echo) {
	tcgetattr(0, &old); /* grab old terminal i/o settings */
	t_new = old; /* make new settings same as old settings */
	t_new.c_lflag &= ~ICANON; /* disable buffered i/o */
	t_new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
	tcsetattr(0, TCSANOW, &t_new); /* use these new terminal i/o settings now */
}

void GraphicsIO::resetTermios() {
	tcsetattr(0, TCSANOW, &old);
}

char GraphicsIO::getch_(int echo) {
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

char GraphicsIO::getch() {
	return getch_(1);
}

char GraphicsIO::getche() {
	return getch_(1);
}

void GraphicsIO::gotoxy(int x, int y) {
	printf("%c[%d;%df",0x1B,y,x);
}
