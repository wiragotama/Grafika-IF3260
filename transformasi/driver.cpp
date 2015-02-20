#include "TerjunPayung.h"

int main() {
	Canvas canvas;
	Point topLeftPosition(100,100);
	TerjunPayung terjunPayung(&canvas, topLeftPosition);
	while (true) {
		terjunPayung.draw();
		sleep(1);
		terjunPayung.moveDown(20);
	}
	return 0;
}