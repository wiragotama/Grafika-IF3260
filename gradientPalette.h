#ifndef GRADIENT_H
#define GRADIENT_H

#include "header.h"
#include "canvas.h"

#define GRADIENTPALETTE_WIDTH 256
#define GRADIENTPALETTE_HEIGHT 256
#define CELLSIZE 1
#define radius MOUSE_RADIUS

class GradientPalette {
	public :
		GradientPalette(int x_offset, int y_offset);
		~GradientPalette();
		
		void drawColorGradient(uint32_t color, Canvas *canvas);
		void drawCursor(Canvas *canvas);
		void moveCursor(char c);
		
		void setXOffset(int x);
		void setYOffset(int y);
		void setCursorX(int x);
		void setCursorY(int y);
		
		int getXOffset();
		int getYOffset();
		int getCursorX(); //mendapatkan posisi kursor pada gradient palette (lokal)
		int getCursorY(); //mendapatkan posisi kursor pada gradient palette (lokal)
		int getCoorXCursor(); //mendapatkan posisi kursor pada pixel di layar (global)
		int getCoorYCursor(); //mendapatkan posisi kursor pada pixel di layar (global)
		
	private :
		int x_offset;
		int y_offset;
		int cursor_x;
		int cursor_y;
};

#endif

