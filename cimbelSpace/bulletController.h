#ifndef BULLET_CONTROLLER_H
#define BULLET_CONTROLLER_H
#include "../cimbelSpace/bullet.h"
#include <vector>

class BulletController {
	public :
		BulletController();
		~BulletController();
		
		bool crashCheck(Point objTopLeft, Point objBottomRight);
		void addBullet(Point topLeftPosition, int direction);
		void garbageCollector();
		void draw(Canvas *canvas, uint32_t color);
		void move(int dx, int dy);
		
	private :
		vector<Bullet> bullets;
};

#endif
