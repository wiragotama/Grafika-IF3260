#ifndef MAP_H
#define MAP_H

class map {
	public:
		map();
		~map();
		void windowToView(Canvas *canvas);
		void zoomIn();
		void zoomOut();
	private:
		 moveViewFrame(int,int);
	private:
		vector<Polygon> islands;
		Point[2] viewFrame;
		int size_width;
		int size_height;
	
};
#endif
