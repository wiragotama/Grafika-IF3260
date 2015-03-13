#include "../core/header.h"
#include "../core/graphicsio.h"
#include "../core/canvas.h"
#include "../colorpicker/rainbowPalette.h"
#include "../colorpicker/gradientPalette.h"
#include "../transformasi/helikopter.h"
#include "../transformasi/drawable.h"
#include "../perang-perangan/animation.h"
#include "../perang-perangan/projectile.h"
#include "../transformasi/TerjunPayung.h"
#include "../cimbelSpace/bulletController.h"

void gameIntroduction(Helikopter* helikopter, Canvas* canvas);
void showRainbowPalette(Helikopter* helikopter, Canvas* canvas);
void gamePlay(Helikopter* helikopter, Canvas *canvas);


int main() {
	Canvas canvas;
	Point topLeftPosition(540,400);
	Helikopter helikopter(topLeftPosition);
	
	//gameIntroduction(&helikopter, &canvas);
	gamePlay(&helikopter, &canvas);
	return 0;
}

void showRainbowPalette(Helikopter* helikopter, Canvas* canvas) {
	
	char c;
	string msgPalette = "Rainbow palette";
	string msgGradient = "Gradient palette (your choise)";
	
	GraphicsIO graphicsIO;
	
	int x_offset = (canvas->get_vinfo().xres - COLORTABLE_WIDTH*COLORTABLE_CELLSIZE)/5;
	int x_offset0 = x_offset + COLORTABLE_WIDTH*COLORTABLE_CELLSIZE + 100;
	int y_offset = (canvas->get_vinfo().yres - COLORTABLE_HEIGHT*COLORTABLE_CELLSIZE)/2 - 50;
	
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
		
		helikopter->setColor(gradientPalette.getColorTable(gradientPalette.getCursorX(), gradientPalette.getCursorY()));
		//helikopter->setColor(canvas->getColor(gradientPalette.getScreenX(), gradientPalette.getScreenY()));
		helikopter->draw(canvas, helikopter->getColor());
		canvas->flush();
		
		canvas->putColorInfo(rainbowPalette.getScreenX(), rainbowPalette.getScreenY(), msgPalette.c_str());
		canvas->putColorInfo(gradientPalette.getScreenX(), gradientPalette.getScreenY(), msgGradient.c_str());
		
		c = graphicsIO.getch();
		rainbowPalette.moveCursor(c);
		gradientPalette.moveCursor(c);
		
	} while (c!='\n');
}

void gameIntroduction(Helikopter* helikopter, Canvas* canvas) {
	system("clear");
	printf("Suatu ketika... \n");
	printf("perang intergalaxy terbesar terjadi di galaxy cimbelSakti...\n");
	printf("--- Tim cimbelExtension --- \n");
	printf("menciptakan pesawat terhebat untuk menangkan perang tersebut...\n");
	printf("Anda TERPILIH untuk menjadi pilot dari pesawat hebat tersebut...\n");
	getchar();
	showRainbowPalette(helikopter, canvas);
	canvas->clearScreen();
}

void gamePlay(Helikopter* helikopter, Canvas *canvas) {
	
	BulletController bulletController;
	GraphicsIO graphicsIO;
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_ENABLE);
	
	char c;
	do {
		bulletController.draw(canvas, canvas->pixel_color(0,0,255));
		helikopter->draw(canvas, helikopter->getColor());
		
		canvas->flush();
		
		int i = GraphicsIO::kbhit();
		if (i!=0) {
			c = fgetc(stdin);
			if (c=='f') {
				Point TLP(helikopter->getTopLeftPosition().getAbsis(), helikopter->getTopLeftPosition().getOrdinat()-11);
				bulletController.addBullet(TLP, 1);
			}
			else if (c == 97 && helikopter->getTopLeftPosition().getAbsis() > 0) { //left gradient
				helikopter->move(-2, 0);
			}
			else if (c == 100 && helikopter->getTopLeftPosition().getAbsis() + helikopter->getWidth() < 640) { //right gradient
				helikopter->move(2, 0);
			}
		}
		bulletController.move(0, -2);
		bulletController.garbageCollector();
		//Point BRP(helikopter->getTopLeftPosition().getAbsis()+helikopter->getWidth(), helikopter->getTopLeftPosition().getOrdinat()+helikopter->getHeight());
		//bulletController.crashCheck(helikopter->getTopLeftPosition(), BRP);
		
	} while (c!='\n');
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_DISABLE);
}
