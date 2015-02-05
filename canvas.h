#ifndef CANVAS_H
#define CANVAS_H

#include "header.h"

class Canvas {
	public :
		Canvas();
		~Canvas();
		
		uint32_t getRainbowColor(double position);
		uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b);
		void putPixelRGB(int screen_x, int screen_y, uint8_t r, uint8_t g, uint8_t b);
		void putPixelColor(int screen_x, int screen_y, uint32_t color); //letakkan warna pada koordinat screen_x,screen_y di layar
		void putColorInfo(int screen_x, int screen_y, const char* message); //mengeluarkan nomor warna rgb pada koordinat screen_x,screen_y di layar
		long getCursorLocation(int screen_x, int screen_y); //mendapatkan lokasi pixel (angka pointer utk framebuffer) dari cursor pada koordinat screen_x,screen_y di layar
		uint32_t getColor(int screen_x, int screen_y); //mendapatkan warna yang sedang ditunjuk kursor pada koordinat screen_x,screen_y di layar
		
		void clearScreen();
		
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
