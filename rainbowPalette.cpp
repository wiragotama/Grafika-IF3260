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
			 color_table[y][x] = canvas->giveRainbowColor(colorRainbow);
			 colorRainbow+=(1.0/(double)(COLORTABLE_HEIGHT*COLORTABLE_WIDTH));
		}
	}
}

void RainbowPalette::drawCursor(Canvas *canvas) {
	int x, y;
	int coor_x = getCoorXCursor();
	int coor_y = getCoorYCursor();
      
	for (y = coor_y-radius; y <= coor_y+radius; y++) {
		for (x = coor_x-radius; x <= coor_x+radius; x++) {
			if ((y==coor_y || x==coor_x) && !(y==coor_y && x==coor_x)) {
				canvas->putPixelRGB(x, y, 255, 255, 255);
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


int RainbowPalette::getCursorX() {
	return cursor_x;
}

int RainbowPalette::getCursorY() {
	return cursor_x;
}
	
int RainbowPalette::getCoorXCursor() {
	return x_offset + (cursor_x*COLORTABLE_CELLSIZE);
}

int RainbowPalette::getCoorYCursor() {
	return y_offset + (cursor_y*COLORTABLE_CELLSIZE);
}

uint32_t RainbowPalette::getColorTable(int pos_width, int pos_height) {
	return color_table[pos_height][pos_width];
}
