#include "../core/header.h"
#include "../core/graphicsio.h"
int main() {
	GraphicsIO graphicsIO;
	char c;
	do {
		system("clear");
		c = graphicsIO.getch();
		printf("haha %d", c);
	} while (c!='\n');
}