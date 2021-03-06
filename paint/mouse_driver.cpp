#include <iostream>
#include <cstdio>
#include "mouse.h"
#include "rectangle_controller.h"
#include "triangle_controller.h"
#include "circle_controller.h"
#include "polygon_controller.h"
#include "../core/graphicsio.h"
#include "colorPickerController.h"

int main() {
    Canvas canvas;
    canvas.setCurrentColor(canvas.pixel_color(255, 255, 0));
	Mouse& mouse = Mouse::getInstance();

	mouse.setX(320);
	mouse.setY(240);

	RectangleController* rectangleController = new RectangleController(&canvas);
    TriangleController* triangleController = new TriangleController(&canvas);
    CircleController* circleController = new CircleController(&canvas);
    PolygonController* polygonController = new PolygonController(&canvas);
    MouseListener* mouseListener = new MouseListener(&canvas);
    mouse.registerListener(mouseListener);
    mouse.startListening();
	// wait for enter
	char c;
    do {
        c = getchar();

        if (c == 49) { //kode ascii untuk 1
            getchar();
            mouse.stopListening();
            mouse.registerListener(rectangleController);
            mouse.startListening();

        } else if (c == 50) {
            getchar();
            mouse.stopListening();
            mouse.registerListener(triangleController);
            mouse.startListening();

        } else if (c == 51) {
            getchar();
            mouse.stopListening();
            mouse.registerListener(circleController);
            mouse.startListening();

		} else if (c == 52) {
			getchar();
			mouse.stopListening();
			mouse.registerListener(polygonController);
			mouse.startListening();

        } else if (c == 53) {
			getchar();
			mouse.stopListening();
			canvas.savePersistentBuffer();
			canvas.resetPersistentBuffer();
			canvas.setCurrentColor(colorPicker(&canvas));
			canvas.loadPersistentBuffer();
			mouse.startListening();

		} else if (c == 54) {
			getchar();
			canvas.resetPersistentBuffer();
		}

        if (c == '\n') mouse.stopListening();
    } while (c!='\n');

    return 0;
}
