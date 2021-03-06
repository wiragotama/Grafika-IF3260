#ifndef GRAPHICS_IO_H
#define GRAPHICS_IO_H

#include <termios.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

using namespace std;

class GraphicsIO {
	public :
		GraphicsIO(); //initTermios
		~GraphicsIO();
		
		void initTermios(int echo);
		void resetTermios();
		char getch_(int echo);
		char getch();
		char getche();
		void gotoxy(int x, int y);
		
		static void nonblock(int state);
		static int kbhit();
		
	public:
		static const int NONBLOCK_ENABLE = 0;
		static const int NONBLOCK_DISABLE = 1;
	private :
		struct termios old;
		struct termios t_new;
};

#endif

/* Reference :
 * 	http://stackoverflow.com/questions/8683526/gotoxy-implementation-for-linux-using-printf
 *	http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
 */
