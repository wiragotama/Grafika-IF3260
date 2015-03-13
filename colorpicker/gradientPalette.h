#ifndef GRADIENT_H
#define GRADIENT_H

#include "../core/header.h"
#include "../core/canvas.h"

#define GRADIENTPALETTE_WIDTH 256
#define GRADIENTPALETTE_HEIGHT 256
#define CELLSIZE 1

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
		int getScreenX(); //mendapatkan posisi kursor pada pixel di layar (global)
		int getScreenY(); //mendapatkan posisi kursor pada pixel di layar (global)
		uint32_t getColorTable(int pos_width, int pos_height);
		
	private :
		int x_offset;
		int y_offset;
		int cursor_x;
		int cursor_y;
		uint32_t color_table[GRADIENTPALETTE_WIDTH][GRADIENTPALETTE_HEIGHT];
};

#endif

