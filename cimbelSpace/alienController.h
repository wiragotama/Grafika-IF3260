#ifndef ALIEN_CONTROLLER_H
#define ALIEN_CONTROLLER_H
#include "../cimbelSpace/bullet.h"
#include "../pattern/polygon.h"
#include <vector>

class AlienController {
	public :
		AlienController();
		~AlienController();
		
		bool crashDelete(Point objTopLeft, Point objBottomRight);
		void addAlien(Point topLeftPosition);
		void garbageCollector();
		void draw(Canvas *canvas, uint32_t color);
		void move(int dx, int dy);
		void deleteAlien(int idx);
		Polygon getAlien(int idx);
		int getSize();
		
		vector<Polygon> getAliens();
		
	private :
		vector<Polygon> aliens;
		static const string alienInfo;
};

#endif
