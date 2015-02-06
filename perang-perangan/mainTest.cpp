#include "header.h"
#include "graphicsio.h"
#include "canvas.h"
#include "line.h"

int main() {
	
	GraphicsIO graphicsIO;
	Canvas canvas;
	char c;
	
	canvas.clearScreen();
	Line newLine(Point(20,30), Point(500,200));
	do {
		newLine.drawLine(&canvas, STRAIGHT_LINE);
		c = graphicsIO.getch();
	}	while (c!='\n');
	return 0;
}
