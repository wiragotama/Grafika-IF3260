#ifndef _POINT_H
#define _POINT_H


class Point {
	public :
		Point();
		Point(double new_x, double new_y); 
		//Default copy constructor, destructor, assignment
		
		double getAbsis() const;
		double getOrdinat() const;
		void setAbsis(double x);
		void setOrdinat(double y);
		
		bool operator==(const Point p) const;
		
	private :
		double x;
		double y;
};

#endif
