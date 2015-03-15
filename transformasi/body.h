#ifndef BODY_H
#define BODY_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/point.h"
#include "../core/line.h"
#include "../pattern/polygon.h"
#include <vector>

#define colorRP 0
#define colorGP 255
#define colorBP 0

#define bodyPath "helikopterBody/body.info"
#define leftBody "helikopterBody/bodyLeft.info"
#define rightBody "helikopterBody/bodyRight.info"
#define bodyPattern "helikopterBody/bodyPattern.info"

class Body {
	public:
		Body(Point topLeftPosition);
		~Body();
		
		void draw(Canvas *canvas, uint32_t color);
		void move(int dx, int dy);
		void broke(); //memecah body (hancur)
		void setTopLeftPosition(Point topLeftPosition);
		Point getTopLeftPosition();
		
		bool getBrokenFlag() const; //mendapatkan petanda apakah body terpecah atau tidak
		void separateBrokenParts(int dx, int dy);
		int getWidth() const;
		int getHeight() const;
        vector<Polygon> getPolygons() const;
		
	private :
		vector<Polygon> polygons;
		bool broken;
		Point topLeftPosition;
};

#endif
