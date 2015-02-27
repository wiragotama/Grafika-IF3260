#include "kincir.h"
#include <cstdio>

double thirtyDegree = 0.5235987756;

int main() {
	Canvas canvas;
    Kincir lonte(&canvas);
    int i = 0;
	while (i < 3) {
        lonte.draw();
        lonte.rotate(thirtyDegree);
        lonte.move(0, -25);
        canvas.flush();
        sleep(1);
        i++;
	}

    while (true) {
        lonte.draw();
        lonte.rotate(thirtyDegree);
        lonte.move(0, -25);
        canvas.flush();
        sleep(1);
        lonte.destroy();
    }
	return 0;
}
