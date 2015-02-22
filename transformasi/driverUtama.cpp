#include "helikopter.h"
#include "drawable.h"
#include "../perang-perangan/animation.h"
#include "../perang-perangan/projectile.h"

bool cekTabrakan(Projectile *p, Helikopter *h);

int main() {
	Canvas canvas;
	Point topLeftPosition(130,50);
	
	Helikopter helikopter(&canvas, topLeftPosition);
	
	Point topLeftPositionKapal(1,400);
	
	Polygon kapal(&canvas, topLeftPositionKapal);
	string polygonFile = "kapal.info"; //nama file jgn sampe salah ya... nanti kena segfault
	kapal.loadPolygon(polygonFile.c_str());
	
	bool direction = true; //left = true, right = false;
	bool kenaPeluru = false;
	
	Projectile p(&canvas, 2);
	p.setTopLeftPosition(Point(91,380));
	
	while(!kenaPeluru) {
		helikopter.draw(canvas.pixel_color(255,0,0));
		kapal.draw(canvas.pixel_color(0,255,0));	
		p.draw();
		
		canvas.flush();
		if (direction) {
			helikopter.move(-1, 0);
		}	
		else {
			helikopter.move(1, 0);
		}
		
		if (helikopter.getTopLeftPosition().getAbsis() <= 10) {
			direction = false;
		}
		else if (helikopter.getTopLeftPosition().getAbsis()+helikopter.getWidth() >= canvas.get_vinfo().xres) {
			direction = true;
		}
		p.move(1, -1);
		if (cekTabrakan(&p, &helikopter)) {
			kenaPeluru = true;
		}
		usleep(5000);
	}
	//ceritanya bagian ini dah kena peluru
	helikopter.brokeBody();
	bool stopMoveDown = false;
	while (true) {
		helikopter.draw(canvas.pixel_color(255,0,0));
		kapal.draw(canvas.pixel_color(0,255,0));
		canvas.flush();
		if (!stopMoveDown)
			helikopter.move(0,1);
		if (helikopter.atBottomOfScreen()) {
			helikopter.bounceTire();
			bool stopMoveDown = true;
		}
		usleep(5000);
	}
	return 0;
}

bool cekTabrakan(Projectile *p, Helikopter *h) {
	return (p->TLPos().getOrdinat() <= h->getTopLeftPosition().getOrdinat()+h->getHeight());
}
