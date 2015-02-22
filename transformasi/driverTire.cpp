#include "tire.h"
#include "../core/header.h"

int main() {
	Canvas canvas;
	Point topLeftPosition(100,100);
	Tire tire(topLeftPosition, 5);
	while (true) {
		tire.draw(&canvas, canvas.pixel_color(255,0,0));
		canvas.flush();
	}
	return 0;
}
