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
        Polygon(Point topLeftPosition, vector<Point> nodes, Point firePoint, Pattern pattern_t);
        Polygon(const Polygon& ply);
        const Polygon& operator=(const Polygon&);
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
		void setTopLeftPosition(Point p);
		Point getPoint(int idx);
		vector<Point> getPoints() const;
		vector<Line> getLines() const;
		Point getFirePoint() const;
		Point getOriginFirePoint() const;
		Point getTopLeftPosition() const;
		Point getMostRightPoint() const;
		Point getMostLeftPoint() const;
		Point getMostBottomPoint() const;
		Point getMostUpperPoint() const;
		Point getBottomRightPoint() const;
        int getMaxY() const;
        int getMinY() const;
        int getMinX() const;
        int getMaxX() const;

		int getWidth() const;
		int getHeight() const;

		void erasePoints();

		Pattern getPattern() const;
		Polygon resizing(double scale, int pivot_x, int pivot_y);
		
		Point getSuitableFirePoint(Canvas* canvas);
		void simulateFloodFill(int x, int y, uint32_t** matrix, Point TLP, Point BRP);
		static bool sortTopLeft(const Polygon& lhs, const Polygon& rhs);
		bool isPointInside(Point p) const;
		
	private :
        void init();
		uint32_t getColor(int x, int y);
		void floodFill(Canvas*, int screen_x, int screen_y, uint32_t color);
		void floodFillBackground(Canvas*, int screen_x, int screen_y, uint32_t color);
		
		/*
		void floodFill(Canvas*, int screen_x, int screen_y);
		void floodFillBackground(Canvas*, int screen_x, int screen_y);*/
	private :
		vector<Point> points;
		Pattern pattern;
		Point firePoint;
		Point originFirePoint;
		Point topLeftPosition;

        mutable int max_x, max_y, min_x, min_y;
};

#endif
