#include "../cimbelSpace/bulletController.h"

BulletController::BulletController() {
}

BulletController::~BulletController() {
}

bool BulletController::crashCheck(Point objTopLeft, Point objBottomRight) {
	bool crash = false;
	for (int i=0; i<bullets.size() && !crash; i++) {
		
		if (bullets[i].getTopLeftPosition().getOrdinat() <= objBottomRight.getOrdinat() &&
		
		((bullets[i].getTopLeftPosition().getAbsis() + bullets[i].getWidth() <= objBottomRight.getAbsis() &&
		bullets[i].getTopLeftPosition().getAbsis() + bullets[i].getWidth() >= objTopLeft.getAbsis()) ||
		
		(bullets[i].getTopLeftPosition().getAbsis() <= objBottomRight.getAbsis() &&
		bullets[i].getTopLeftPosition().getAbsis() >= objTopLeft.getAbsis()) )
		) {
			crash = true;
		}
		else if (bullets[i].getTopLeftPosition().getOrdinat()+bullets[i].getHeight() >= objTopLeft.getOrdinat() &&
		
		((bullets[i].getTopLeftPosition().getAbsis() + bullets[i].getWidth() <= objBottomRight.getAbsis() &&
		bullets[i].getTopLeftPosition().getAbsis() + bullets[i].getWidth() >= objTopLeft.getAbsis()) ||
		
		(bullets[i].getTopLeftPosition().getAbsis() <= objBottomRight.getAbsis() &&
		bullets[i].getTopLeftPosition().getAbsis() >= objTopLeft.getAbsis()) )
		) {
			crash = true;
		}
	}
	return crash;
}

void BulletController::addBullet(Point topLeftPosition, int direction) {
	Bullet temp(direction, topLeftPosition);
	bullets.push_back(temp);
}

void BulletController::garbageCollector() {
	int idx = 0;
	while (idx < bullets.size()) {
		if (bullets[idx].getFlag()==true) {
			bullets.erase(bullets.begin()+idx);
		}
		else idx++;
	}
}

void BulletController::draw(Canvas *canvas, uint32_t color) {
	for (int i=0; i<bullets.size(); i++)
		bullets[i].draw(canvas, color);
}

void BulletController::move(int dx, int dy) {
	for (int i=0; i<bullets.size(); i++)
		bullets[i].move(dx, dy);
}
