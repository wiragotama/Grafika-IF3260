#include "../core/header.h"
#include "../core/graphicsio.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "kapal.h"
#include "pesawat.h"
#include "animation.h"
#include "projectile.h"

double diffTimeMs(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

int main() {
	GraphicsIO graphicsIO;
	Canvas canvas;
	struct fb_var_screeninfo vinfo = canvas.get_vinfo();
	char c;
	
	vector<Animation*> animations;
	
	Kapal* the_kapal = new Kapal(&canvas);
	the_kapal->setTopLeftPosition(Point(0, vinfo.yres-the_kapal->getHeight()));
	Pesawat* the_plane = new Pesawat(&canvas);
	the_plane->setTopLeftPosition(Point(vinfo.xres-the_plane->getWidth(), 0));
	animations.push_back(the_kapal);
	animations.push_back(the_plane);

	clock_t lastClock = clock();
	double delta = 0;
	double timePerFrame = 1000.0/60;
	canvas.clearScreen();
	clock_t lastFireKapal = clock();
	clock_t lastFirePesawat = clock();
	
	bool stop = false;
	while(!stop) {
		clock_t nowClock = clock();
		delta += diffTimeMs(nowClock, lastClock);
		lastClock = nowClock;
		if(delta >= timePerFrame){
			delta -= timePerFrame;
			//bersih-bersih projectile
			if (animations.size()>2) {
				int idx = 2;
				while (idx!=animations.size()-1) {
					if (animations[idx]->getFlag() == true) {
						animations.erase(animations.begin()+idx);
					}
					else idx++;
				}
			}
			//Update
			for(int i=0; i<animations.size(); i++){
				if (animations[i]!=NULL)
					animations[i]->update(timePerFrame);
			}
			//Render
			for(int i=0; i<animations.size(); i++) {
				if (animations[i]!=NULL)
					animations[i]->draw();
					if (animations.size()>=2 && i<2) {
						for (int j=2; j<animations.size() && !stop; j++) {
							if (animations[i]->isCollide(*animations[j])) {
								animations[i]->explode();
								stop = true;
							}
						}
					}
			}
			canvas.flush();
		}
		if (lastClock-lastFireKapal > 7000000) {
			Projectile* p = new Projectile(&canvas, 1);
			p->setTopLeftPosition(the_kapal->fire());
			animations.push_back(p);
			lastFireKapal = nowClock;
		}
		if (lastClock-lastFirePesawat > 2000000) {
			Projectile* p = new Projectile(&canvas, 2);
			p->setTopLeftPosition(the_plane->fire());
			animations.push_back(p);
			lastFirePesawat = nowClock;
		}
	}
	/*Kapal kapal(&canvas);
	do {
		kapal.draw();
		c = graphicsIO.getch();
	}	while (c!='\n');*/
	return 0;
}
