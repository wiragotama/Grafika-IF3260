#include "gradientPalette.h"

GradientPalette::GradientPalette(int x_offset, int y_offset) {
	this->x_offset = x_offset;
	this->y_offset = y_offset;
	cursor_x = 255;
	cursor_y = 255;
}

GradientPalette::~GradientPalette() {}

void GradientPalette::drawColorGradient(uint32_t color, Canvas *canvas) {
	int x, y;
	uint8_t rr = (color >> canvas->get_vinfo().red.offset) & 0xFF,
	    gg = (color >> canvas->get_vinfo().green.offset) & 0xFF,
		bb = (color >> canvas->get_vinfo().blue.offset) & 0xFF;
	uint8_t r, g, b;
	for (y = 0; y < GRADIENTPALETTE_HEIGHT; y++) {
		for (x = 0; x < GRADIENTPALETTE_WIDTH; x++) {
			r = (y * (255-x) + rr * x * y / 255)/255;
			g = (y * (255-x) + gg * x * y / 255)/255;
			b = (y * (255-x) + bb * x * y / 255)/255;
			this->color_table[y][x] = canvas->pixel_color(r,g,b);
			canvas->putPixelColor(x_offset+x, y_offset+y, canvas->pixel_color(r,g,b));
		}
	}
}

void GradientPalette::drawColorGradientPersistent(uint32_t color, Canvas *canvas) {
	int x, y;
	uint8_t rr = (color >> canvas->get_vinfo().red.offset) & 0xFF,
	    gg = (color >> canvas->get_vinfo().green.offset) & 0xFF,
		bb = (color >> canvas->get_vinfo().blue.offset) & 0xFF;
	uint8_t r, g, b;
	for (y = 0; y < GRADIENTPALETTE_HEIGHT; y++) {
		for (x = 0; x < GRADIENTPALETTE_WIDTH; x++) {
			r = (y * (255-x) + rr * x * y / 255)/255;
			g = (y * (255-x) + gg * x * y / 255)/255;
			b = (y * (255-x) + bb * x * y / 255)/255;
			this->color_table[y][x] = canvas->pixel_color(r,g,b);
			canvas->putPixelColorPersistent(x_offset+x, y_offset+y, canvas->pixel_color(r,g,b));
		}
	}
}

void GradientPalette::drawCursor(Canvas *canvas) {
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

void GradientPalette::moveCursor(char c) {
	if(c==97 && cursor_x>0) {//left gradient
		cursor_x--;
	}
	else if (c==119 && cursor_y>0) { //up gradient
		cursor_y--;
	}
	else if (c==100 && cursor_x<255) { //right gradient
		cursor_x++;
	}
	else if (c==115 && cursor_y<255) { //down gradient
		cursor_y++;
	}
}

void GradientPalette::setXOffset(int x) {
	x_offset = x;
}

void GradientPalette::setYOffset(int y) {
	y_offset = y;
}

void GradientPalette::setCursorX(int x) {
	cursor_x = x;
}

void GradientPalette::setCursorY(int y) {
	cursor_y = y;
}

int GradientPalette::getXOffset() {
	return x_offset;
}

int GradientPalette::getYOffset() {
	return y_offset;
}

int GradientPalette::getCursorX() { //mendapatkan posisi kursor pada gradient palette (lokal)
	return cursor_x;
}

int GradientPalette::getCursorY() { //mendapatkan posisi kursor pada gradient palette (lokal)
	return cursor_y;
}

int GradientPalette::getScreenX() { //mendapatkan posisi kursor pada pixel di layar (global)
	return x_offset + (cursor_x*CELLSIZE);
}

int GradientPalette::getScreenY() { //mendapatkan posisi kursor pada pixel di layar (global)
	return y_offset + (cursor_y*CELLSIZE);
}

uint32_t GradientPalette::getColorTable(int pos_width, int pos_height) {
	return color_table[pos_height][pos_width];
}

int GradientPalette::getTopLeftX() {
	return x_offset;
}

int GradientPalette::getTopLeftY() {
	return y_offset;
}

int GradientPalette::getBottomRightX() {
	return x_offset + GRADIENTPALETTE_WIDTH;
}

int GradientPalette::getBottomRightY() {
	return y_offset + GRADIENTPALETTE_HEIGHT;
}

