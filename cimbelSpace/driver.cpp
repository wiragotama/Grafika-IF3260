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
#include "../peta3d/peta3d.h"
#include <ctime>

void gameIntroduction(Helikopter* helikopter, Canvas* canvas);
void showRainbowPalette(Helikopter* helikopter, Canvas* canvas);
void gamePlay(Helikopter* helikopter, Canvas *canvas, Peta3D& petaIndonesia);
void keyHandle(char c, BulletController* bulletController, Helikopter *helikopter);
void cleanUp(BulletController* bulletController, AlienController *alienController);
bool planeCrash(AlienController *alienController, Helikopter* helikopter);

// Eric method
const string nama_pulau[] = {"Jawa", "Kalimantan", "Papua", "Sulawesi", "Sumatera"};
int x_rect[] = {185-10, 372+10, 141-10, 314+10, 449-10, 639+10, 340-10, 426+10, 14-10, 159+10}; // posisi x_min, x_max
int y_rect[] = {365-10, 424+10, 59-10, 263+10, 60-10, 227+10, 65-10, 276+10, 78-10, 402+10}; // posisi y_min, y_max

void drawSelector(Canvas& canvas, int kode_pulau);
void animatePulau(Canvas& canvas, Peta3D& petaIndonesia, int kode_pulau);
int selectPulau(Canvas& canvas, GraphicsIO& graphicsIO, Peta3D& petaIndonesia);

int main() {
	Canvas canvas;
	GraphicsIO graphicsIO;
	Point topLeftPosition(540,400);
	Helikopter helikopter(topLeftPosition);
	Peta3D petaIndonesia;

	petaIndonesia.findTheShit(x_rect, y_rect);

	bool game_not_end = true;

	gameIntroduction(&helikopter, &canvas);
	while (true) {
		int selected = selectPulau(canvas, graphicsIO, petaIndonesia);
		if (selected == -1) break;
		animatePulau(canvas, petaIndonesia, selected);
		showRainbowPalette(&helikopter, &canvas);
		canvas.clearScreen();
		gamePlay(&helikopter, &canvas, petaIndonesia);
	}

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






int selectPulau(Canvas& canvas, GraphicsIO& graphicsIO, Peta3D& petaIndonesia) {
	int current_selection = 0; // jawa
	const int byk_pulau = sizeof(x_rect)/sizeof(int)/2;

	char c;

	do {
		system("clear"); // reset the printf printing position
		petaIndonesia.drawPeta3d(&canvas);
		drawSelector(canvas, current_selection);
		canvas.flush();
		cout << nama_pulau[current_selection] << endl;
		cout.flush();

		c = graphicsIO.getch();
		switch (c) {
			case 'w':
				current_selection--;
				if (current_selection == -1)
					current_selection = byk_pulau-1;
				break;
			case 's':
				current_selection++;
				if (current_selection == byk_pulau)
					current_selection = 0;
				break;
			case 'q':
				return -1;
		}
	} while (c!='\n');

	return current_selection;
}

void drawSelector(Canvas& canvas, int kode_pulau) {
	int i1 = 2*kode_pulau, i2 = i1+1;

	Polygon poly( Point(x_rect[i1], y_rect[i1]) ,
				  Point(x_rect[i2], y_rect[i2]) );

	uint32_t cyan = canvas.pixel_color(0, 255, 255);
	poly.draw(&canvas, cyan);
}

void animatePulau(Canvas& canvas, Peta3D& petaIndonesia, int kode_pulau) {
	const int animate_time = 2000; // 2 detik
	const int num_frame = 20;
	const int MAX_X = 640, MAX_Y = 480;
	const double time_per_frame = (double)animate_time/num_frame;

	const int i1 = 2*kode_pulau, i2 = i1+1;

	const double dxl = ((double)-x_rect[i1]) / num_frame,
		dxr = ( MAX_X - (double)x_rect[i2] ) / num_frame,
		dyt = ((double)-y_rect[i1]) / num_frame,
		dyb = ( MAX_Y - (double)y_rect[i2] ) / num_frame;

	for (int i = num_frame-1; i >= 0; --i) {
		clock_t before = clock(), current;

		const int x_min = round(x_rect[i1] + dxl*i),
			x_max = round(x_rect[i2] + dxr*i),
			y_min = round(y_rect[i1] + dyt*i),
			y_max = round(y_rect[i2] + dyb*i);

		Polygon poly( Point(x_min, y_min) ,
			          Point(x_max, y_max) );

		petaIndonesia.setHighlightedArea(poly);
		petaIndonesia.drawPetaClipping(&canvas);
		canvas.flush();

		// busy wait until time passes
		while (i > 0) {
			current = clock();
			double est = (current-before)*1000/CLOCKS_PER_SEC;
			if (est >= time_per_frame)
				break;
		}
	}
}





void gameIntroduction(Helikopter* helikopter, Canvas* canvas) {
	system("clear");
	printf("Suatu ketika... \n");
	printf("perang intergalaxy terbesar terjadi di galaxy cimbelSakti...\n");
	printf("--- Tim cimbelExtension --- \n");
	printf("menciptakan pesawat terhebat untuk menangkan perang tersebut...\n");
	printf("Anda TERPILIH untuk menjadi pilot dari pesawat hebat tersebut...\n");
	getchar();
}

void gamePlay(Helikopter* helikopter, Canvas *canvas, Peta3D& petaIndonesia) {

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

		petaIndonesia.drawPetaClipping(canvas);
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
	petaIndonesia.drawPetaClipping(canvas);
	helikopter->draw(canvas, helikopter->getColor());
	canvas->flush();
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_DISABLE);
	getchar();
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
