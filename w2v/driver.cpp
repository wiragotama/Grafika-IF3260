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
	char c;
	Canvas canvas;
	Peta peta;
	GraphicsIO graphicsIO;
	peta.showHighlightedArea(&canvas);
	do {
		peta.windowToView(&canvas);
		canvas.flush();

		c = graphicsIO.getch();

		peta.moveHighlightedArea(c,&canvas);
	} while (c!='\n');

	return 0;
}
