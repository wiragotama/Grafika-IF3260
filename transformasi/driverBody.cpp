#include "body.h"

int main() {
	Canvas canvas;
	Point topLeftPosition(50,50);
	Body body(&canvas, topLeftPosition);
	//while (true) {
		body.broke();
		body.draw(canvas.pixel_color(255,0,0));
		canvas.flush();
		//sleep(1);
		//body.move(20);
	//}
	return 0;
}
