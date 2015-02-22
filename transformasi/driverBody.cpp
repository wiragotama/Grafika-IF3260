#include "body.h"

int main() {
	Canvas canvas;
	Point topLeftPosition(50,50);
	Body body(&canvas, topLeftPosition);
	//while (true) {
		body.broke();
		body.draw();
		//sleep(1);
		//body.move(20);
	//}
	return 0;
}
