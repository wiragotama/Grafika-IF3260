#ifndef PETA_H
#define PETA_H

#include "../core/header.h"
#include "../core/canvas.h"
#include "../core/line.h"
#include "../core/point.h"
#include "../pattern/polygon.h"

class Peta {
	public:
		Peta();
		~Peta();
		void windowToView(Canvas*);
		void zoomIn();
		void zoomOut();
		void show_s_view_frame(Canvas*);
	private:
		void loadFile(const char*);

	private:
		vector<Polygon> islands;
		Point viewFrame[2];
		int size_width;
		int size_height;		
		Polygon s_view_frame;		
};
#endif
