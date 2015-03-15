#ifndef POLYGON_H
#define POLYGON_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/point.h"
#include "../core/line.h"
#include "../pattern/pattern.h"

class Polygon {
	public :
		Polygon();
		Polygon(Point topLeftPosition);
		Polygon(Point topLeft, Point botRight);
        Polygon(Point topLeftPosition, vector<Point> nodes, Point firePoint, Pattern pattern_t);
        Polygon(const Polygon& ply);
        const Polygon& operator=(const Polygon&);
		~Polygon();

		void draw(Canvas*, uint32_t color);
		void drawBackground(Canvas*, uint32_t color);
		void move(int dx, int dy);
		void loadPolygon(const char* filename); //mengambil informasi titik-titik penyusun polygon
		void loadPattern(const char *filename); //mengambil informasi pattern yang akan digunakan untuk filling polygon
        Polygon rotate(double angle, int rx, int ry);
        void printInfo(); //print data polygon ke layar
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
        int getMaxY() const; //mendapatkan batas ordinat atas polygon
        int getMinY() const; //mendapatkan batas ordinat bawah polygon
        int getMinX() const; //mendapatkan batas absis bawah polygon
        int getMaxX() const; //mendapatkan batas absis atas polygon

		int getWidth() const;
		int getHeight() const;

		void erasePoints();

		Pattern getPattern() const;
		Polygon resizing(double scale, int pivot_x, int pivot_y);

		Point getSuitableFirePoint(Canvas* canvas); //mencari firePoint yang cocok untuk polygon, dibantu dengan simulasi flood fill dari batas absis dan ordinat polygon
		void simulateFloodFill(int x, int y, uint32_t** matrix, Point TLP, Point BRP); //mensimulasikan flood fill
		static bool sortTopLeft(const Polygon& lhs, const Polygon& rhs);
		bool isPointInside(Point p) const;

	private :
        void init();
		uint32_t getColor(int x, int y);
		void floodFill(Canvas*, int screen_x, int screen_y, uint32_t color); //flood fill dengan bantuan dirty bit -> untuk polygon yang berada diatas objek lain di layar
		void floodFillBackground(Canvas*, int screen_x, int screen_y, uint32_t color); //flood fill tanpa bantuan dirty bit -> untuk polygon yang bertindak sebagai background

	private :
		vector<Point> points;
		Pattern pattern;
		Point firePoint;
		Point originFirePoint;
		Point topLeftPosition;

        mutable int max_x, max_y, min_x, min_y;
};

#endif
