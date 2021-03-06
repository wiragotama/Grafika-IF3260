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

		//tambahan
		void flushPersistent();
		void resetPersistentBuffer();
		void putPixelColorPersistent(int screen_x, int screen_y, uint32_t color);

		void setCurrentColor(uint32_t);
		uint32_t getCurrentColor();
		void loadPersistentBuffer();
		void savePersistentBuffer();

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
		uint8_t *persistentBuffer;
		uint8_t *backupBuffer;
		uint8_t *fbp;

		uint32_t currentColor;
};

#endif
