#include <iostream>
#include <cstdio>
#include <vector>
#include "point3D.h"
#include "cube.h"
#include "camera3d.h"
#include "point.h"
#include "polygon.h"
#include "canvas.h"
#include "graphicsio.h"

using namespace std;

int main() {
	Cube kubus;
	Camera3D camera3d;
	
	Canvas canvas;
	GraphicsIO graphicsIO;
	char c;
	
	do {
		vector<Polygon> cubeSurfaces; 
		
		vector< std::pair<double, std::vector<Point3D> > > cube2d = kubus.project_sides(camera3d);
		for(int i=0; i<cube2d.size(); i++){
			//printf("%lf\n", cube2d[i].first );
			vector<Point3D> points3d = cube2d[i].second;
			vector<Point> points2d;
			for(int j=0; j<points3d.size(); j++){
				//printf("(%lf,%lf)", points3d[j].getX(), points3d[j].getY());
				points2d.push_back(Point(points3d[j].getX()*100+300, points3d[j].getY()*100+300));
			}
			cubeSurfaces.push_back(Polygon(points2d));
			//printf("\n\n");
			
		}
		
		for(int i=0; i<(int)cubeSurfaces.size(); i++){
			cubeSurfaces[i].draw(&canvas, canvas.pixel_color(255,255,255));
		}
		
		canvas.flush();		
		
		c = graphicsIO.getch();
		
		if (c == 97) { //left arrow
			double radian = camera3d.getAzimuth();
			radian += (M_PI)/100;
			if(radian >= M_PI*2)
				radian-= M_PI*2;
			camera3d.setAzimuth(radian);
		} 
		else if (c == 119) { //up arrow
			double radian = camera3d.getPolar();
			radian += (M_PI)/100;
			if(radian >= M_PI)
				radian-= M_PI;
			camera3d.setPolar(radian);
		}
		else if (c == 100) { //right arrow
			double radian = camera3d.getAzimuth();
			radian -= (M_PI)/100;
			if(radian < 0.0)
				radian+= M_PI*2;
			camera3d.setAzimuth(radian);
		}
		else if (c == 115) { //down arrow
			double radian = camera3d.getPolar();
			radian -= (M_PI)/100;
			if(radian < 0.0)
				radian+= M_PI;
			camera3d.setPolar(radian);
		}
		
		//camera3d.printAxes();
		
	} while (c != '\n');
	
	return 0;
}
