#include <iostream>
#include <cstdio>
#include "mouse.h"
#include "rectangle_controller.h"
#include "triangle_controller.h"
#include "../core/graphicsio.h"

int main() {
    Canvas canvas;
    canvas.setCurrentColor(canvas.pixel_color(255, 255, 0));
	Mouse& mouse = Mouse::getInstance();

	mouse.setX(320);
	mouse.setY(240);

	RectangleController* rectangleController = new RectangleController(&canvas);
    TriangleController* triangleController = new TriangleController(&canvas);
    MouseListener* mouseListener = new MouseListener(&canvas);
    mouse.registerListener(mouseListener);
    mouse.startListening();
	// wait for enter
	char c;
    do {
        c = getchar();

        // printf("%d\n", c == 49); //49 kode ascii untuk 1
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
        }

        // int x = mouse.getX();
        // int y = mouse.getY();
        // canvas.flush();
        if (c == '\n') mouse.stopListening();
    } while (c!='\n');

	/*
    int fd;
    struct input_event ie;

    unsigned char button,bLeft,bMiddle,bRight;
    char x,y;


    printf("right-click to set absolute x,y coordinates origin (0,0)\n");
    while(read(fd, &ie, sizeof(struct input_event)))
    {
        unsigned char *ptr = (unsigned char*)&ie;
        int i;

        button=ptr[0];
        bLeft = button & 0x1;
        bMiddle = ( button & 0x4 ) > 0;
        bRight = ( button & 0x2 ) > 0;
        x=(char) ptr[1];y=(char) ptr[2];
        printf("bLEFT:%d, bMIDDLE: %d, bRIGHT: %d, rx: %d  ry=%d\n",bLeft,bMiddle,bRight, x,y);

        absolute_x+=x;
        absolute_y-=y;
        if (bRight==1)
        {
            absolute_x=0;
            absolute_y=0;
            printf("Absolute x,y coords origin recorded\n");
        }

        printf("Absolute coords from TOP_LEFT= %i %i\n",absolute_x,absolute_y);
        //
        // comment to disable the display of raw event structure datas
        //
        for(i=0; i<sizeof(ie); i++)
        {
            printf("%02X ", *ptr++);
        }
        printf("\n");
    }
    */

    return 0;
}
