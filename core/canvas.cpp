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
	fbp = (uint8_t*) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, (off_t)0);
}

Canvas::~Canvas() {
	delete[] backbuffer;
	close(fbfd);
}

uint32_t Canvas::pixel_color(uint8_t r, uint8_t g, uint8_t b) {
	return (r<<vinfo.red.offset) | (g<<vinfo.green.offset) | (b<<vinfo.blue.offset);
}

uint32_t Canvas::getRainbowColor(double position) {
	if (position>1.0){if (position-(int)position==0.0)position=1.0; else position=position-(int)position;}

	unsigned char nmax=6; /* number of color segments */
	double m=nmax* position;

	char c[3];
	int n=(int)m; // integer of m

	double f=m-n;  // fraction of m
	unsigned char t=(int)(f*255);

	switch( n){
		case 0: {
			c[0] = 255;
			c[1] = t;
			c[2] = 0;
			break;
		};
		case 1: {
			c[0] = 255 - t;
			c[1] = 255;
			c[2] = 0;
			break;
		};
		case 2: {
			c[0] = 0;
			c[1] = 255;
			c[2] = t;
			break;
		};
		case 3: {
			c[0] = 0;
			c[1] = 255 - t;
			c[2] = 255;
			break;
		};
		case 4: {
			c[0] = t;
			c[1] = 0;
			c[2] = 255;
			break;
		};
		case 5: {
			c[0] = 255;
			c[1] = 0;
			c[2] = 255 - t;
			break;
		};
		default: {
			c[0] = 255;
			c[1] = 0;
			c[2] = 0;
			break;
		};
	}; // case
	return pixel_color(c[0],c[1],c[2]);
}

void Canvas::putPixelColor(int screen_x, int screen_y, uint32_t color) { //letakkan warna pada koordinat screen_x,screen_y di layar
	long location = getCursorLocation(screen_x,screen_y);
	if(location >= getScreensize() || location < 0);
		//nothing
	else { 
		*((uint32_t*)(backbuffer + location)) = color | 0xff000000; //dirty bit untuk menandakan sudah pernah menulis di tempat itu
	}
}

void Canvas::putBackgroundPixel(int screen_x, int screen_y, uint32_t color) {
	long location = getCursorLocation(screen_x,screen_y);
	if(location >= getScreensize() || location < 0);
		//nothing
	else { 
		*((uint32_t*)(backbuffer + location)) = color; //dirty bit untuk menandakan sudah pernah menulis di tempat itu
	}
}

void Canvas::resetDirtyBit(int screen_x, int screen_y, int screen_x2, int screen_y2) {
	for (int i=screen_x; i<screen_x2; i++)
		for (int j=screen_y; j<screen_y2; j++) {
			long location = getCursorLocation(i,j);
			if(location >= getScreensize() || location < 0);
				//nothing
			else { 
				*((uint32_t*)(backbuffer + location)) &= 0xFFFFFF;  //dirty bit untuk menandakan sudah pernah menulis di tempat itu
			}
	}
}

long Canvas::getCursorLocation(int screen_x, int screen_y) { //mendapatkan lokasi pixel (angka pointer utk framebuffer) dari cursor pada posisi coor_x,coor_y di layar
	if (screen_x >=0 && screen_y>=0 && screen_x <=vinfo.xres && screen_y <= vinfo.yres)
		return (screen_x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (screen_y+vinfo.yoffset) * finfo.line_length;
	else
		return -1; //diluar jangkauan
}

uint32_t Canvas::getColor(int screen_x, int screen_y) { //mendapatkan warna yang sedang ditunjuk kursor pada koordinat screen_x,screen_y di layar
	return *((uint32_t*)(fbp + getCursorLocation(screen_x, screen_y)));
}

uint32_t Canvas::getColor(long location) { //mendapatkan warna yang ditunjuk pada location
	if (location >=getScreensize() || location <0)
		return -1;
	else 
		return *((uint32_t*)(backbuffer+location));
}

void Canvas::clearScreen() {
	for(int i=0; i<get_vinfo().yres; i++)
		for(int j=0; j<get_vinfo().xres; j++)
			putPixelColor(j,i,0);
}

void Canvas::flush() {
	memcpy(fbp, backbuffer, screensize);
	memset(backbuffer,0,screensize);
}

/* getter */
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

void Canvas::putColorInfo(int screen_x, int screen_y, const char* message) { //mengeluarkan nomor warna rgb pada koordinat screen_x,screen_y di layar
	long location = getCursorLocation(screen_x,screen_y);
	printf("Warna %s: %#08x\n",message,*((uint32_t*)(fbp + location)));
}
