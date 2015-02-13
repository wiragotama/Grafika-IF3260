#ifndef PATTERN_H
#define PATTERN_H

#include "../core/header.h"

class Pattern {
	public :
		Pattern();
		~Pattern();

		void loadFile(const char *filename);
		void setElement(int row, int column, uint32_t color);
		int getColor(int row, int column);
		int getWidth();
		int getHeight();
		
	private :
		uint32_t **matrix;
		int width;
		int height;
};

#endif
