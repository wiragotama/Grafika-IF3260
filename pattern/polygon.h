#ifndef POLYGON_H
#define POLYGON_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/point.h"
#include "../core/header.h"
#include "../core/line.h"
#include "../pattern/pattern.h"

class Polygon {
	public :
		Polygon();
		Polygon(Point topLeftPosition);
        Polygon(Point topLeftPosition, vector<Point> nodes, Point firePoint);
        Polygon(const Polygon& ply);
		~Polygon();

		void draw(Canvas*, uint32_t color);
		void drawBackground(Canvas*, uint32_t color);
		void move(int dx, int dy);
		void loadPolygon(const char* filename);
		void loadPattern(const char *filename);
        Polygon rotate(double angle, int rx, int ry);
        void printInfo();
		void addPoint(Point P);
		
		/* Setter & Getter */
		void setPoint(int idx, Point P);
		void setFirePoint(Point P);
		void setTopLeftPosition(int x, int y);
		Point getPoint(int idx);
		vector<Point> getPoints() const;
		Point getFirePoint() const;
		Point getOriginFirePoint() const;
		Point getTopLeftPosition() const;
		Point getMostRightPoint();
		Point getMostLeftPoint();
		Point getMostBottomPoint();
		Point getMostUpperPoint();
		void erasePoints();
		
		Pattern getPattern() const;
		
	private :
		uint32_t getColor(int x, int y);
		void floodFill(Canvas*, int screen_x, int screen_y);
		void floodFillBackground(Canvas*, int screen_x, int screen_y);
		
	private :
		vector<Point> points;
		Pattern pattern;
		Point firePoint;
		Point originFirePoint;
		Point topLeftPosition;
};

#endif
