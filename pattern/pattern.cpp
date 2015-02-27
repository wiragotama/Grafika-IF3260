#include "../pattern/pattern.h"
Pattern::Pattern() {
	this->width = 0;
	this->height = 0;
	matrix = NULL;
}

Pattern::Pattern(const Pattern& pattern) {
	uint32_t** other = pattern.getMatrix();
	if (other!=NULL) {
		width = pattern.getWidth();
		height = pattern.getHeight();
		
		matrix = new uint32_t* [height];
		for (int i = 0; i < height; i++) {
			matrix[i] = new uint32_t[width];
			memcpy(matrix[i], other[i], sizeof(uint32_t)*width);
		}
		
	} else {
		matrix = NULL;
		width = 0;
		height = 0;
	}
}

const Pattern& Pattern::operator=(const Pattern& pattern) {
	uint32_t** other = pattern.getMatrix();
	if (other!=NULL) {
		width = pattern.getWidth();
		height = pattern.getHeight();
		
		matrix = new uint32_t* [height];
		for (int i = 0; i < height; i++) {
			matrix[i] = new uint32_t[width];
			memcpy(matrix[i], other[i], sizeof(uint32_t)*width);
		}
		
	} else {
		matrix = NULL;
		width = 0;
		height = 0;
	}
	return *this;
}

Pattern::~Pattern() {
	if (matrix!=NULL) {
		for (int i = 0; i < height; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
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
	fclose(matrix_file);
}

void Pattern::setElement(int row, int column, uint32_t color) {
	matrix[row][column] = color;
}

int Pattern::getColor(int row, int column) {
	return matrix[row%height][column%width];
}

int Pattern::getWidth() const {
	return width;
}

int Pattern::getHeight() const {
	return height;
}

uint32_t** Pattern::getMatrix() const {
	return matrix;
}
