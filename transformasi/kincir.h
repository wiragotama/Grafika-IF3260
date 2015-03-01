#ifndef KINCIR_H
#define KINCIR_H

#include <cstdio>
#include <vector>
#include "../core/point.h"
#include "../core/canvas.h"
#include "../pattern/polygon.h"

#define kincir1Path "kincirInfo/kincir1.info"
#define kincir2Path "kincirInfo/kincir2.info"
#define kincir3Path "kincirInfo/kincir3.info"
#define kincir4Path "kincirInfo/kincir4.info"
#define kincirPattern "kincirInfo/kincirPattern.info"

class Kincir {
    public:
		Kincir();
		Kincir(Point centerPoint);
		Kincir(int x, int y);
		Kincir(const Kincir&);
		const Kincir& operator= (const Kincir&);
		~Kincir();

		void destroy();
		void draw(Canvas *p_canvas, uint32_t color);
		void rotate(double radians);
		void move(int dx, int dy);

        vector<Polygon> getPolygons() const;

    private:
		void init();

		vector<Polygon> orig, transformed;
		Point center;
		double angle;

		static const double PI;
};

#endif
