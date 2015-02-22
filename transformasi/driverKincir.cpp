#include "kincir.h"
#include <cstdio>

double thirtyDegree = 0.5235987756;

int main() {
	Canvas canvas;
    Kincir lonte(&canvas);
	while (true) {
        lonte.draw();
        lonte.rotate(thirtyDegree);
        canvas.flush();
        sleep(1);
	}
	return 0;
}
