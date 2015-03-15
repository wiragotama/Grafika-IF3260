#include "../core/header.h"
#include "../core/graphicsio.h"
#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "../core/point.h"
#include "../pattern/polygon.h"
#include "../transformasi/helikopter.h"
#include "peta3d.h"

int main() {
	char c;
	Canvas canvas;
	GraphicsIO graphicsIO;
	Peta3D petaIndonesia;
	
	//Membuat input nonblocking
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_ENABLE);
	
	do {
		petaIndonesia.drawPeta3d(&canvas);
		
		canvas.flush();

		int i = GraphicsIO::kbhit();
		if(i != 0){
			c=fgetc(stdin);
				if (c == 97) { //left gradient
					petaIndonesia.moveHighlightedArea(-1,0,&canvas);
				}
				else if (c == 119) { //up gradient
					petaIndonesia.moveHighlightedArea(0,-1,&canvas);
				}
				else if (c == 100) { //right gradient
					petaIndonesia.moveHighlightedArea(1,0,&canvas);
				}
				else if (c == 115) { //down gradient
					petaIndonesia.moveHighlightedArea(0,1,&canvas);
				} else if (c == 45) { //zoomout //tanda (-)
					petaIndonesia.zoomOut(&canvas);
				} else if (c == 43) {
					petaIndonesia.zoomIn();
				}
			// petaIndonesia.moveHighlightedArea(c);
			// if (c == 97) { //left arrow
			// 	petaIndonesia.move(1,0);
			// }
			// else if (c == 119) { //up arrow
			// 	petaIndonesia.move(0,1);
			// }
			// else if (c == 100) { //right arrow
			// 	petaIndonesia.move(-1,0);
			// }
			// else if (c == 115) { //down arrow
			// 	petaIndonesia.move(0,-1);
			// }
		}
		
	} while (c != '\n');
	
	//Membuat input kembali blocking
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_DISABLE);
		
	return 0;
}
