#ifndef GRAPHICS_IO_H
#define GRAPHICS_IO_H

#include "header.h"

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
		
	private :
		struct termios old;
		struct termios t_new;
};

#endif

/* Reference :
 * 	http://stackoverflow.com/questions/8683526/gotoxy-implementation-for-linux-using-printf
 *	http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
 */
