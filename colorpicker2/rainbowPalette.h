#ifndef RAINBOW_H
#define RAINBOW_H

#include "../core/header.h"
#include "../3D_Perspective/canvas.h"
#define COLORTABLE_WIDTH 35
#define COLORTABLE_HEIGHT 256
#define COLORTABLE_CELLSIZE 1

class RainbowPalette {
	public :
		RainbowPalette(int x_offset, int y_offset);
		~RainbowPalette();
		
		void initRainbowColor(Canvas *canvas);
		void drawCursor(Canvas *canvas);
		void drawPalette(Canvas *canvas);
		void moveCursor(char c);
		
		void setXOffset(int x);
		void setYOffset(int y);
		void setCursorX(int x);
		void setCursorY(int y);
		void setColorTable(int pos_width, int pos_height, uint32_t color);
		int getXOffset();
		int getYOffset();
		int getCursorX(); //mendapatkan posisi kursor pada rainbow palette (lokal)
		int getCursorY(); //mendapatkan posisi kursor pada rainbow palette (lokal)
		int getScreenX(); //mendapatkan posisi kursor pada pixel di layar (global)
		int getScreenY(); //mendapatkan posisi kursor pada pixel di layar (global)
		uint32_t getColorTable(int pos_width, int pos_height);
		uint32_t getRainbowColor(double position, Canvas *canvas);
		
		int getTopLeftX();
		int getTopLeftY();
		int getBottomRightX();
		int getBottomRightY();
		
	private :
		int x_offset;
		int y_offset;
		int cursor_x;
		int cursor_y;
		uint32_t color_table[COLORTABLE_HEIGHT][COLORTABLE_WIDTH];
};

#endif

