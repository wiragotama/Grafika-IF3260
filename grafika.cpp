#include "header.h"
#include "graphicsio.h"
#include "canvas.h"
#include "rainbowPalette.h"
#include "gradientPalette.h"

int main() {
	char c;
	string msgPalette = "rainbow palette";
	string msgGradient = "gradient palette";
	
	GraphicsIO graphicsIO;
	Canvas canvas;
	
	int x_offset = (canvas.get_vinfo().xres - COLORTABLE_WIDTH*COLORTABLE_CELLSIZE)/5;
	int x_offset0 = x_offset + COLORTABLE_WIDTH*COLORTABLE_CELLSIZE + 100;
	int y_offset = (canvas.get_vinfo().yres - COLORTABLE_HEIGHT*COLORTABLE_CELLSIZE)/2;
	
	RainbowPalette rainbowPalette(x_offset, y_offset);
	GradientPalette gradientPalette(x_offset0, y_offset);
	
	rainbowPalette.initRainbowColor(&canvas);
	do {
		system("clear");
		rainbowPalette.drawPalette(&canvas);
		rainbowPalette.drawCursor(&canvas);
		canvas.putColorInfo(rainbowPalette.getCoorXCursor(), rainbowPalette.getCoorYCursor(), msgPalette.c_str());
		
		gradientPalette.drawColorGradient(canvas.getColor(rainbowPalette.getCoorXCursor(),rainbowPalette.getCoorYCursor()), &canvas);
		gradientPalette.drawCursor(&canvas);
		canvas.putColorInfo(gradientPalette.getCoorXCursor(), gradientPalette.getCoorYCursor(), msgGradient.c_str());
		
		c = graphicsIO.getch();
		rainbowPalette.moveCursor(c);
		gradientPalette.moveCursor(c);
	} while (c!='\n');
	return 0;
}
