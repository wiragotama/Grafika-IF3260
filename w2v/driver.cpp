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
<<<<<<< HEAD
	GraphicsIO graphicsIO;
	peta.showHighlightedArea(&canvas);
	do {
		system("clear");
		peta.windowToView(&canvas);
		peta.showSmallViewFrame(&canvas);
		canvas.flush();
		
		c = graphicsIO.getch();
		
		peta.moveHighlightedArea(c,&canvas);
	}
	while (c!='\n');
=======
	peta.windowToView(&canvas);
	canvas.flush();
>>>>>>> 7804fdff1e06e83f0387c58400a88c6a3327f12f
	return 0;
}
