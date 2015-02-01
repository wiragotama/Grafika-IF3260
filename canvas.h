#ifndef CANVAS_H
#define CANVAS_H

#include "header.h"

class Canvas {
	public :
		Canvas();
		~Canvas();
		
		uint32_t giveRainbowColor(double position);
		uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b);
		void putPixelRGB(int x, int y, uint8_t r, uint8_t g, uint8_t b);
		void putPixelColor(int x, int y, uint32_t color);
		void putColorInfo(int cursor_x, int cursor_y, const char* message);
		long getCursorLocation(int coor_x, int coor_y); //mendapatkan koordinat pixel tengah dari curcor_x dan cursor_y di layar
		uint32_t getColor(int coor_x, int coor_y); //mendapatkan warna yang sedang ditunjuk kursor pada posisi coor_x, coor_y di layar
		
		/* getter */
		struct fb_fix_screeninfo get_finfo();
		struct fb_var_screeninfo get_vinfo();
		int get_fbfd();
		long getScreensize();
	
	private :
		struct fb_fix_screeninfo finfo;
		struct fb_var_screeninfo vinfo;
		int fbfd;
		long screensize;
		uint8_t *fbp;
};

#endif
