#ifndef CANVAS_H
#define CANVAS_H

#include <linux/fb.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>


class Canvas {
	public :
		Canvas();
		~Canvas();
		
		uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b);
		void putPixelColor(int screen_x, int screen_y, uint32_t color); 
		uint32_t getColor(int screen_x, int screen_y);

		void clearScreen();
		void flush();

		//for colorpicker purpose
		struct fb_fix_screeninfo get_finfo();
		struct fb_var_screeninfo get_vinfo();
	
	private:
		/**
		 *  Mendapatkan lokasi pixel (angka pointer utk framebuffer)
		 *  dari cursor pada koordinat screen_x,screen_y di layar
		 *  Mengembalikan -1 jika diluar layar 
		 **/
		long getCursorLocation(int screen_x, int screen_y);
		
		int get_fbfd();
		long getScreensize();
	
		struct fb_fix_screeninfo finfo;
		struct fb_var_screeninfo vinfo;
		int fbfd;
		long screensize;
		uint8_t *backbuffer;
		uint8_t *fbp;
};

#endif
