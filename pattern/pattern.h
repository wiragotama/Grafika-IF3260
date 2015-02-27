#ifndef PATTERN_H
#define PATTERN_H

#include "../core/header.h"

class Pattern {
	public :
		Pattern();
		Pattern(const Pattern& pattern);
		~Pattern();

		void loadFile(const char *filename);
		void setElement(int row, int column, uint32_t color);
		int getColor(int row, int column);
		int getWidth() const;
		int getHeight() const;
		uint32_t** getMatrix() const;
		
	private :
		uint32_t **matrix;
		int width;
		int height;
};

#endif
