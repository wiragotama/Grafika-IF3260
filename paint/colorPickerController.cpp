#include "colorPickerController.h"

uint32_t colorPicker(Canvas *canvas) {
	char c;
	GraphicsIO graphicsIO;

	int x_offset = (canvas->get_vinfo().xres - COLORTABLE_WIDTH*COLORTABLE_CELLSIZE)/5;
	int x_offset0 = x_offset + COLORTABLE_WIDTH*COLORTABLE_CELLSIZE + 100;
	int y_offset = (canvas->get_vinfo().yres - COLORTABLE_HEIGHT*COLORTABLE_CELLSIZE)/2;

	RainbowPalette rainbowPalette(x_offset, y_offset);
	GradientPalette gradientPalette(x_offset0, y_offset);

	rainbowPalette.initRainbowColor(canvas);
	do {
		system("clear");
		rainbowPalette.drawPalette(canvas);
		rainbowPalette.drawCursor(canvas);

		canvas->flush();
		rainbowPalette.drawPalette(canvas);
		rainbowPalette.drawCursor(canvas);
		gradientPalette.drawColorGradient(canvas->getColor(rainbowPalette.getScreenX(),rainbowPalette.getScreenY()), canvas);
		gradientPalette.drawCursor(canvas);
		canvas->flush();

		//canvas.putColorInfo(rainbowPalette.getScreenX(), rainbowPalette.getScreenY(), msgPalette.c_str());
		//canvas.putColorInfo(gradientPalette.getScreenX(), gradientPalette.getScreenY(), msgGradient.c_str());

		c = graphicsIO.getch();
		rainbowPalette.moveCursor(c);
		gradientPalette.moveCursor(c);
	} while (c!='\n');
	return canvas->getColor(rainbowPalette.getScreenX(), rainbowPalette.getScreenY());
}
