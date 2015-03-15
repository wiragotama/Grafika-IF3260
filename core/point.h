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
		int getAbsis() const;
		int getOrdinat() const;
		void setAbsis(int x);
		void setOrdinat(int y);
        void printInfo();
        bool isOrigin() const;
        bool isEqual(Point p) const;
		/* Move on screen */
		void moveRight(int d);
		void moveLeft(int d);
		void moveUp(int d);
		void moveDown(int d);
		void move(int dx, int dy);
        void rotate(double angle, int rx, int ry);
        static int orientation(Point p, Point q, Point r);
		static bool pointGreaterThan(Point a, Point b);
		static bool sortUpperLeft(const Point& lhs, const Point& rhs);
		static bool ccw (Point p, Point q, Point r);
		
	private :
		int x;
		int y;
};

#endif
