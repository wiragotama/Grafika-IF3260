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
	return getch_(0);
}

char GraphicsIO::getche() {
	return getch_(1);
}

void GraphicsIO::gotoxy(int x, int y) {
	printf("%c[%d;%df",0x1B,y,x);
}

void GraphicsIO::nonblock(int state){
	struct termios ttystate;
 
    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
 
    if (state==NONBLOCK_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state==NONBLOCK_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}


int GraphicsIO::kbhit(){
	struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 33000;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
