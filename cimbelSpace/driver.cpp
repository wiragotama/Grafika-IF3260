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
#include "../cimbelSpace/alienController.h"
#include <ctime>

void gameIntroduction(Helikopter* helikopter, Canvas* canvas);
void showRainbowPalette(Helikopter* helikopter, Canvas* canvas);
void gamePlay(Helikopter* helikopter, Canvas *canvas);
void keyHandle(char c, BulletController* bulletController, Helikopter *helikopter);
void cleanUp(BulletController* bulletController, AlienController *alienController);
bool planeCrash(AlienController *alienController, Helikopter* helikopter);

int main() {
	// Polygon poly;
	// poly.addPoint(Point(0,0));
	// poly.addPoint(Point(100,0));
	// poly.addPoint(Point(100,100));
	// poly.addPoint(Point(0,100));
	// poly.addPoint(Point(0,0));
	// poly.draw(&canvas, canvas.pixel_color(255,0,0));
	// canvas.flush();
	// int x1,y;
	// cin >> x1 >> y;
	// bool x = poly.isPointInside(Point(x1,y));
	// cout << "di dalam polygon ga? " << x << endl; //coy ini blm bisa jalan soalnya masalah di include2
	Canvas canvas;
	Point topLeftPosition(540,400);
	Helikopter helikopter(topLeftPosition);

	gameIntroduction(&helikopter, &canvas);
	gamePlay(&helikopter, &canvas);
	return 0;
}

void showRainbowPalette(Helikopter* helikopter, Canvas* canvas) {

	char c;
	string msgPalette = "Rainbow palette";
	string msgGradient = "Gradient palette (your choice)";

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
	AlienController alienController;

	GraphicsIO graphicsIO;
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_ENABLE);

	char c;
	int timeCounter = 0;
	bool planeBroke = false;
	do {
		srand(time(NULL));
		int rand_var = rand()%640 + 1; //posisi random spawn monster
		if (timeCounter==200) {
			//spawn monster
			Point ATLP(rand_var, 1);
			alienController.addAlien(ATLP);
			timeCounter = 0;
		}

		bulletController.draw(canvas, canvas->pixel_color(0,0,255));
		alienController.draw(canvas, canvas->pixel_color(218,165,32));
		helikopter->draw(canvas, helikopter->getColor());

		canvas->flush();

		int i = GraphicsIO::kbhit();
		if (i!=0) {
			c = fgetc(stdin);
			keyHandle(c, &bulletController, helikopter);
		}
		bulletController.move(0, -2);
		alienController.move(0, 2);
		//bersih2
		planeBroke = planeCrash(&alienController, helikopter);
		cleanUp(&bulletController, &alienController);
		timeCounter++;

	} while (c!='\n' && !planeBroke);
	helikopter->draw(canvas, helikopter->getColor());
	canvas->flush();
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_DISABLE);
}

void keyHandle(char c, BulletController* bulletController, Helikopter *helikopter) {
	if (c=='f') {
		Point TLP(helikopter->getTopLeftPosition().getAbsis(), helikopter->getTopLeftPosition().getOrdinat()-11);
		bulletController->addBullet(TLP, 1);
	}
	else if (c == 97 && helikopter->getTopLeftPosition().getAbsis() > 0) { //left gradient
		helikopter->move(-2, 0);
	}
	else if (c == 100 && helikopter->getTopLeftPosition().getAbsis() + helikopter->getWidth() < 640) { //right gradient
		helikopter->move(2, 0);
	}
}

void cleanUp(BulletController* bulletController, AlienController *alienController) {
	if (alienController->getSize() > 0) {
		for (int i=0; i<bulletController->getSize();) {
			Point BRP(bulletController->getBullet(i).getTopLeftPosition().getAbsis() + bulletController->getBullet(i).getWidth(),
					bulletController->getBullet(i).getTopLeftPosition().getOrdinat() + bulletController->getBullet(i).getHeight());
			bool flag = alienController->crashDelete(bulletController->getBullet(i).getTopLeftPosition(), BRP);
			if (flag) {
				bulletController->deleteBullet(i);
			}
			else i++;
		}
	}
	alienController->garbageCollector();
	bulletController->garbageCollector();
}

bool planeCrash(AlienController *alienController, Helikopter* helikopter) {
	bool flag = false;
	for (int i=0; i<!flag && alienController->getSize(); ) {
		Point BRP(helikopter->getTopLeftPosition().getAbsis() + helikopter->getWidth(),
				helikopter->getTopLeftPosition().getOrdinat() + helikopter->getHeight());
		flag = alienController->crashDelete(helikopter->getTopLeftPosition(), BRP);
		if (flag) {
			helikopter->brokeBody();
		}
		else i++;
	}
	return flag;
}
