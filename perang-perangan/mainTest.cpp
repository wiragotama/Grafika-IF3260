#include "../core/header.h"
#include "../core/graphicsio.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "kapal.h"
#include "animation.h"

double diffTimeMs(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

int main() {

	GraphicsIO graphicsIO;
	Canvas canvas;
	char c;

	vector<Animation*> animations;
	Kapal* the_kapal = new Kapal(&canvas);
	the_kapal->setTopLeftPosition(Point(0, 500));
	animations.push_back(the_kapal);

	clock_t lastClock = clock();
	double delta = 0;
	double timePerFrame = 1000.0/60;
	while(true) {
		clock_t nowClock = clock();
		delta += diffTimeMs(nowClock, lastClock);
		lastClock = nowClock;
		if(delta >= timePerFrame){
			delta -= timePerFrame;
			//Update
			for(int i=0; i<animations.size(); i++){
				animations[i]->update(timePerFrame);
			}
			//Render
			for(int i=0; i<animations.size(); i++){
				animations[i]->draw();
			}
		}
	}
	/*Kapal kapal(&canvas);
	do {
		kapal.draw();
		c = graphicsIO.getch();
	}	while (c!='\n');*/
	return 0;
}
