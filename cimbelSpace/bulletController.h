#ifndef BULLET_CONTROLLER_H
#define BULLET_CONTROLLER_H
#include "../cimbelSpace/bullet.h"
#include <vector>

class BulletController {
	public :
		BulletController();
		~BulletController();
		
		bool crashCheck(Point objTopLeft, Point objBottomRight); //menghapus objek bullet ketika ada tumbukan dengan objek lain
		void addBullet(Point topLeftPosition, int direction); //menambahkan objek bullet baru
		void garbageCollector(); //melakukan bersih-bersih di memory untuk objek bullet yang sudah melewati layar
		void draw(Canvas *canvas, uint32_t color);
		void move(int dx, int dy);
		void deleteBullet(int idx);
		Bullet getBullet(int idx);
		int getSize(); //mendapatkan jumlah bullet yang ada
		
		vector<Bullet> getBullets();
		
	private :
		vector<Bullet> bullets;
};

#endif
