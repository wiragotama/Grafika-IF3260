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
		
	petaIndonesia.drawPeta3d(&canvas);
	
	canvas.flush();
		
	return 0;
}
