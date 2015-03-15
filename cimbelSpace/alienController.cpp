#include "../cimbelSpace/alienController.h"

const string AlienController::alienInfo =  "alien/alien.info";

AlienController::AlienController() {
}

AlienController::~AlienController() {
}



bool AlienController::crashDelete(Point objTopLeft, Point objBottomRight) {
//menghapus objek polygon ketika ada tumbukan dengan objek lain

	bool crash = false;
	for (int i=0; i<aliens.size();) {
		Point tl_a = aliens[i].getTopLeftPosition();
		Point br_a = Point(tl_a.getAbsis()+aliens[i].getWidth() , tl_a.getOrdinat()+aliens[i].getHeight());

		Point tl_c = Point( std::max(tl_a.getAbsis(),objTopLeft.getAbsis()), std::max(tl_a.getOrdinat(),objTopLeft.getOrdinat()) );
		Point br_c = Point( std::min(br_a.getAbsis(),objBottomRight.getAbsis()), std::min(br_a.getOrdinat(),objBottomRight.getOrdinat()) );

		if (!(br_c.getAbsis() < tl_c.getAbsis() || br_c.getOrdinat() < tl_c.getOrdinat())) {	
			crash = true;
			aliens.erase(aliens.begin()+i);
		}
		else i++;
	}
	return cras}

void AlienController::addAlien(Point topLeftPosition) {
//menambahkan objek alien baru

	Polygon temp(topLeftPosition);
	temp.loadPolygon(alienInfo.c_str());
	aliens.push_back(temp);
}

void AlienController::garbageCollector() {
//melakukan bersih-bersih di memory untuk objek alien yang sudah melewati layar

	int idx = 0;
	while (idx < aliens.size()) {
		if (aliens[idx].getTopLeftPosition().getOrdinat()+aliens[idx].getHeight()>=640) {
			aliens.erase(aliens.begin()+idx);
		}
		else idx++;
	}
}

void AlienController::draw(Canvas *canvas, uint32_t color) {
	for (int i=0; i<aliens.size(); i++)
		aliens[i].draw(canvas, color);
}

void AlienController::move(int dx, int dy) {
	for (int i=0; i<aliens.size(); i++)
		aliens[i].move(dx, dy);
}

vector<Polygon> AlienController::getAliens() {
//mengembalikan alien pada index ke-idx

	return aliens;
}

void AlienController::deleteAlien(int idx) {
//menghapus alien pada index ke-idx

	aliens.erase(aliens.begin()+idx);
}

Polygon AlienController::getAlien(int idx) {
	return aliens[idx];
}

int AlienController::getSize() {
//mendapatkan jumlah alien yang ada

	return aliens.size();
}
