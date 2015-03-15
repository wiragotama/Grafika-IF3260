#include "../cimbelSpace/bulletController.h"

BulletController::BulletController() {
}

BulletController::~BulletController() {
}

bool BulletController::crashCheck(Point objTopLeft, Point objBottomRight) {
//menghapus objek bullet ketika ada tumbukan dengan objek lain

	bool crash = false;
	for (int i=0; i<bullets.size() && !crash; i++) {
		Point tl_a = bullets[i].getTopLeftPosition();
		Point br_a = Point(tl_a.getAbsis()+bullets[i].getWidth() , tl_a.getOrdinat()+bullets[i].getHeight());

		Point tl_c = Point( std::max(tl_a.getAbsis(),objTopLeft.getAbsis()), std::max(tl_a.getOrdinat(),objTopLeft.getOrdinat()) );
		Point br_c = Point( std::min(br_a.getAbsis(),objBottomRight.getAbsis()), std::min(br_a.getOrdinat(),objBottomRight.getOrdinat()) );

		if (!(br_c.getAbsis() < tl_c.getAbsis() || br_c.getOrdinat() < tl_c.getOrdinat())) {	
			crash = true;
			bullets.erase(bullets.begin()+i);
		}
		else i++;
	}
	return crash;
}

void BulletController::addBullet(Point topLeftPosition, int direction) {
//menambahkan objek bullet baru

	Bullet temp(direction, topLeftPosition);
	bullets.push_back(temp);
}

void BulletController::garbageCollector() {
//melakukan bersih-bersih di memory untuk objek bullet yang sudah melewati layar

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

vector<Bullet> BulletController::getBullets() {
	return bullets;
}

void BulletController::deleteBullet(int idx) {
	bullets.erase(bullets.begin()+idx);
}
Bullet BulletController::getBullet(int idx) {
	return bullets[idx];
}

int BulletController::getSize() {
//mendapatkan jumlah bullet yang ada

	return bullets.size();
}
