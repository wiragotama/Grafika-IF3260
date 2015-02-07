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

	fbp = (uint8_t*) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, (off_t)0);
}

Canvas::~Canvas() {
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

void Canvas::putPixelRGB(int screen_x, int screen_y, uint8_t r, uint8_t g, uint8_t b) {
	long location = getCursorLocation(screen_x,screen_y);
	if(location >= getScreensize())
		printf("Cetak keluar dari screen\n");
	else
		*((uint32_t*)(fbp + location)) = pixel_color(r, g, b);
}

void Canvas::putPixelColor(int screen_x, int screen_y, uint32_t color) { //letakkan warna pada koordinat screen_x,screen_y di layar
	long location = getCursorLocation(screen_x,screen_y);
	*((uint32_t*)(fbp + location)) = color;
}

void Canvas::putColorInfo(int screen_x, int screen_y, const char* message) { //mengeluarkan nomor warna rgb pada koordinat screen_x,screen_y di layar
	long location = getCursorLocation(screen_x,screen_y);
	printf("Warna %s: %#08x\n",message,*((uint32_t*)(fbp + location)));
}

long Canvas::getCursorLocation(int screen_x, int screen_y) { //mendapatkan lokasi pixel (angka pointer utk framebuffer) dari cursor pada posisi coor_x,coor_y di layar
	return (screen_x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (screen_y+vinfo.yoffset) * finfo.line_length;
}

uint32_t Canvas::getColor(int screen_x, int screen_y) { //mendapatkan warna yang sedang ditunjuk kursor pada koordinat screen_x,screen_y di layar
	return *((uint32_t*)(fbp + getCursorLocation(screen_x, screen_y)));
}

void Canvas::clearScreen() {
	for(int i=0; i<get_vinfo().yres; i++)
		for(int j=0; j<get_vinfo().xres; j++)
			putPixelRGB(j,i,0,0,0);
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
