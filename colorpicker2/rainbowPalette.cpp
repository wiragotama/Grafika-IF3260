#include "rainbowPalette.h"

RainbowPalette::RainbowPalette(int x_offset, int y_offset) {
	this->x_offset = x_offset;
	this->y_offset = y_offset;
	cursor_x = 0;
	cursor_y = 0;
}

RainbowPalette::~RainbowPalette() {}

void RainbowPalette::initRainbowColor(Canvas *canvas) {
	int x, y;
	float colorRainbow = 0;
	for(y=0; y<COLORTABLE_HEIGHT ;y++) {
		for(x=0; x<COLORTABLE_WIDTH ;x++) {
			 color_table[y][x] = getRainbowColor(colorRainbow, canvas);
			 colorRainbow+=(1.0/(double)(COLORTABLE_HEIGHT*COLORTABLE_WIDTH));
		}
	}
}

uint32_t RainbowPalette::getRainbowColor(double position, Canvas *canvas) {
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
	return canvas->pixel_color(c[0],c[1],c[2]);
}

void RainbowPalette::drawCursor(Canvas *canvas) {
	int x, y;
	int coor_x = getScreenX();
	int coor_y = getScreenY();
      
	for (y = coor_y-MOUSE_RADIUS; y <= coor_y+MOUSE_RADIUS; y++) {
		for (x = coor_x-MOUSE_RADIUS; x <= coor_x+MOUSE_RADIUS; x++) {
			if ((y==coor_y || x==coor_x) && !(y==coor_y && x==coor_x)) {
				canvas->putPixelColor(x, y, canvas->pixel_color(255,255,255));
			}
		}
	}
}

void RainbowPalette::drawPalette(Canvas *canvas) {
	int x, y;
	if(x_offset>=0 && y_offset>=0){
		for (x=x_offset; x<x_offset+COLORTABLE_WIDTH*COLORTABLE_CELLSIZE; x++)
			for (y=y_offset; y<y_offset+COLORTABLE_HEIGHT*COLORTABLE_CELLSIZE; y++) {
				int colortable_y = (y-y_offset)/COLORTABLE_CELLSIZE;
				int colortable_x = (x-x_offset)/COLORTABLE_CELLSIZE;
				canvas->putPixelColor(x,y,color_table[colortable_y][colortable_x]);
			}
	} 
	else {
		printf("Sreensize not enough\n");
	}
}

void RainbowPalette::drawPalettePersistent(Canvas *canvas) {
	int x, y;
	if(x_offset>=0 && y_offset>=0){
		for (x=x_offset; x<x_offset+COLORTABLE_WIDTH*COLORTABLE_CELLSIZE; x++)
			for (y=y_offset; y<y_offset+COLORTABLE_HEIGHT*COLORTABLE_CELLSIZE; y++) {
				int colortable_y = (y-y_offset)/COLORTABLE_CELLSIZE;
				int colortable_x = (x-x_offset)/COLORTABLE_CELLSIZE;
				canvas->putPixelColorPersistent(x,y,color_table[colortable_y][colortable_x]);
			}
	} 
	else {
		printf("Sreensize not enough\n");
	}
}

int RainbowPalette::getTopLeftX() {
	return x_offset;
}

int RainbowPalette::getTopLeftY() {
	return y_offset;
}

int RainbowPalette::getBottomRightX() {
	return x_offset + x_offset+COLORTABLE_WIDTH*COLORTABLE_CELLSIZE;
}

int RainbowPalette::getBottomRightY() {
	return y_offset + y_offset+COLORTABLE_HEIGHT*COLORTABLE_CELLSIZE;
}

void RainbowPalette::moveCursor(char c) {
	if(c==68 && cursor_x>0) {//Left color 
		cursor_x--;
	}
	else if(c==65 && cursor_y>0) {//up color 
		cursor_y--;
	}
	else if(c==67 && cursor_x<COLORTABLE_WIDTH-1) {//right color
		cursor_x++;
	}
	else if(c==66 && cursor_y<COLORTABLE_HEIGHT-1) {//down color
		cursor_y++;
	}
}

void RainbowPalette::setXOffset(int x) {
	x_offset = x;
}

void RainbowPalette::setYOffset(int y) {
	y_offset = y;
}

void RainbowPalette::setCursorX(int x) {
	cursor_x = x;
}

void RainbowPalette::setCursorY(int y) {
	cursor_y = y;
}

void RainbowPalette::setColorTable(int pos_width, int pos_height, uint32_t color) {
	color_table[pos_height][pos_width] = color;
}

int RainbowPalette::getXOffset() {
	return x_offset;
}

int RainbowPalette::getYOffset() {
	return y_offset;
}


int RainbowPalette::getCursorX() { //mendapatkan posisi kursor pada rainbow palette (lokal)
	return cursor_x;
}

int RainbowPalette::getCursorY() { //mendapatkan posisi kursor pada rainbow palette (lokal)
	return cursor_x;
}
	
int RainbowPalette::getScreenX() { //mendapatkan posisi kursor pada pixel di layar (global)
	return x_offset + (cursor_x*COLORTABLE_CELLSIZE);
}

int RainbowPalette::getScreenY() { //mendapatkan posisi kursor pada pixel di layar (global)
	return y_offset + (cursor_y*COLORTABLE_CELLSIZE);
}

uint32_t RainbowPalette::getColorTable(int pos_width, int pos_height) {
	return color_table[pos_height][pos_width];
}
