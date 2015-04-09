#include "canvas.h"

Canvas::Canvas() {
	fbfd = open("/dev/fb0",O_RDWR);

	//Get variable screen information
	ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
	vinfo.grayscale=0;
	vinfo.bits_per_pixel=32;
	ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo);
	ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);

     //Get fix screen information
	ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);

	screensize = vinfo.yres_virtual * finfo.line_length;

	backbuffer = new uint8_t[screensize];
	persistentBuffer = new uint8_t[screensize];
	fbp = (uint8_t*) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, (off_t)0);
}

Canvas::~Canvas() {
	delete[] backbuffer;
	close(fbfd);
}

uint32_t Canvas::pixel_color(uint8_t r, uint8_t g, uint8_t b) {
	return (r<<vinfo.red.offset) | (g<<vinfo.green.offset) | (b<<vinfo.blue.offset);
}

//letakkan warna pada koordinat screen_x,screen_y di layar
void Canvas::putPixelColor(int screen_x, int screen_y, uint32_t color) { 
	long location = getCursorLocation(screen_x,screen_y);
	if(location >= getScreensize() || location < 0);
		//nothing
	else {
		*((uint32_t*)(backbuffer + location)) = color;
	}
}

//mendapatkan lokasi pixel (pointer ke framebuffer) untuk posisi screen_x, screen_y di layar
long Canvas::getCursorLocation(int screen_x, int screen_y) { 
	if (screen_x >=0 && screen_y>=0 && (unsigned)screen_x <= vinfo.xres && (unsigned) screen_y <= vinfo.yres)
		return (screen_x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (screen_y+vinfo.yoffset) * finfo.line_length;
	else
		return -1; 
}

uint32_t Canvas::getColor(int screen_x, int screen_y) { 
	return *((uint32_t*)(fbp + getCursorLocation(screen_x, screen_y)));
}

void Canvas::clearScreen() {
	for(int i=0; i< (int) get_vinfo().yres; i++)
		for(int j=0; j< (int) get_vinfo().xres; j++)
			putPixelColor(j,i,0);
}

void Canvas::flush() {
	memcpy(fbp, backbuffer, screensize);
	memset(backbuffer,0, screensize);
}

struct fb_fix_screeninfo Canvas::get_finfo() {
	return finfo;
}

struct fb_var_screeninfo Canvas::get_vinfo() {
	return vinfo;
}

int Canvas::get_fbfd() {
	return fbfd;
}

long Canvas::getScreensize() {
	return screensize;
}

void Canvas::putPixelColorPersistent(int screen_x, int screen_y, uint32_t color) { 
	long location = getCursorLocation(screen_x,screen_y);
	if(location >= getScreensize() || location < 0);
		//nothing
	else {
		*((uint32_t*)(persistentBuffer + location)) = color;
	}
}

void Canvas::flushPersistent() {
	memcpy(fbp, persistentBuffer, screensize);
}

void Canvas::resetPersistentBuffer() {
	memset(persistentBuffer,0, screensize);
}
