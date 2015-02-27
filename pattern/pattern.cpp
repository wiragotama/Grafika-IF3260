#include "../pattern/pattern.h"
Pattern::Pattern() {
	this->width = 0;
	this->height = 0;
	matrix = NULL;
}

Pattern::~Pattern() {
	if (matrix!=NULL)
		free(matrix);
}

void Pattern::loadFile(const char *filename) {
	int row, column;
	uint32_t value;
	FILE *matrix_file;
	matrix_file = fopen(filename,"r");

	fscanf(matrix_file, "%d %d", &row, &column);

	this->width = column;
	this->height = row;
	
	matrix = new uint32_t *[row];
	for(int it=0; it<row ; ++it) {
		matrix[it] = new uint32_t [column];
		for (int j=0; j<column; ++j) {
			fscanf(matrix_file, "%u", &value);
			matrix[it][j] = value;
		}
	}
}

void Pattern::setElement(int row, int column, uint32_t color) {
	matrix[row][column] = color;
}

int Pattern::getColor(int row, int column) {
	return matrix[row][column];
}

int Pattern::getWidth() {
	return width;
}

int Pattern::getHeight() {
	return height;
}

uint32_t** Pattern::getMatrix() {
	return matrix;
}
