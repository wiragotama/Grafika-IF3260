#include "peta.h"

Peta::Peta() {}

Peta::~Peta() {}

void Peta::loadFile(const char *filename) {
	int count, p1, p2;
	uint32_t value;
	FILE *file;
	file = fopen(filename,"r");

	fscanf(file, "%d", &count);
	// Polygon polygon();

	for(int it=0; it<count ; ++it) {
		fscanf(file, "%d %d", &p1, &p2);
		// Point p(p1,p2);
		// polygon.addPoint(p);
	}

	// islands.push_back(polygon);
}