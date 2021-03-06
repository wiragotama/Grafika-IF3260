#include "../core/header.h"
#include "peta.h"
#include "../core/graphicsio.h"

int main() {
	char c;
	Canvas canvas;
	Peta peta;
	GraphicsIO graphicsIO;
	peta.showHighlightedArea(&canvas);
	
	//Membuat input nonblocking
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_ENABLE);
	
	do {
		peta.drawIndonesia(&canvas);
        peta.drawHeli(&canvas);
		peta.drawKapal(&canvas);
		peta.showHighlightedArea(&canvas);
		
		canvas.flush();
		
		peta.moveKapal();
		
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
