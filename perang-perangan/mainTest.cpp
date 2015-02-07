#include "../core/header.h"
#include "../core/graphicsio.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "kapal.h"

int main() {

	GraphicsIO graphicsIO;
	Canvas canvas;
	char c;

	canvas.clearScreen();
	Kapal kapal(&canvas);
	do {
		kapal.draw();
		c = graphicsIO.getch();
	}	while (c!='\n');
	return 0;
}

time_t cumulativeTime;
time_t awal = time(null);
while(1) {
	double
}
