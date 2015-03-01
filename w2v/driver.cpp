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
	
	//Membuat input nonblocking
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_ENABLE);
	
	do {
		peta.drawIndonesia(&canvas);
		peta.showHighlightedArea(&canvas);
		
		canvas.flush();
		
		int i = GraphicsIO::kbhit();
		if(i != 0){
			c=fgetc(stdin);
			peta.moveHighlightedArea(c);
		}
		
	} while (c != '\n');
	
	//Membuat input kembali blocking
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_DISABLE);

	return 0;
}
