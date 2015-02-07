/* File : point.h */
/* Author : 13512015 - Jan Wira Gotama Putra */
#ifndef _POINT_H
#define _POINT_H

class Point {
	public :
		Point(); //constructor default tanpa parameter
		Point(int new_x, int new_y); //constructor dengan parameter
		Point(const Point& p); //copy constructor
		virtual Point& operator= (const Point& p); //assignment
		~Point(); //destructor
		int getAbsis();
		int getOrdinat();
		void setAbsis(int x);
		void setOrdinat(int y);
		/* Move on screen */
		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();
		
	private :
		int x;
		int y;
};

#endif
