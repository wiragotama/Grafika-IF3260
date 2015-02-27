#include "../core/header.h"
#include "peta.h"
#include "../core/graphicsio.h"
#include "../transformasi/TerjunPayung.h"
int main() {
	// GraphicsIO graphicsIO;
	// char c;
	// do {
	// 	system("clear");
	// 	c = graphicsIO.getch();
	// 	printf("haha %d", c);
	// } while (c!='\n');
	Canvas canvas;
	Peta peta;
	peta.windowToView(&canvas);
	canvas.flush();
	return 0;
}
