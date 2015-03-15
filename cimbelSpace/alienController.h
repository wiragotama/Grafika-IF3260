#ifndef ALIEN_CONTROLLER_H
#define ALIEN_CONTROLLER_H
#include "../cimbelSpace/bullet.h"
#include "../pattern/polygon.h"
#include <vector>

class AlienController {
	public :
		AlienController();
		~AlienController();
		
		bool crashDelete(Point objTopLeft, Point objBottomRight); //menghapus objek polygon ketika ada tumbukan dengan objek lain
		void addAlien(Point topLeftPosition); //menambahkan objek alien baru
		void garbageCollector(); //melakukan bersih-bersih di memory untuk objek alien yang sudah melewati layar
		void draw(Canvas *canvas, uint32_t color);
		void move(int dx, int dy);
		void deleteAlien(int idx); //menghapus alien pada index ke-idx
		Polygon getAlien(int idx); //mengembalikan alien pada index ke-idx
		int getSize(); //mendapatkan jumlah alien yang ada
		
		vector<Polygon> getAliens(); 
		
	private :
		vector<Polygon> aliens;
		static const string alienInfo;
};

#endif
