#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include "../core/line.h"
#include "../core/header.h"

#define bulletR 0
#define bulletG 0
#define bulletB 255

class Bullet {
	public :
		Bullet(int direction, Point topLeftPosition);
		~Bullet();
		void draw(Canvas *canvas, uint32_t color);
        void update(double timeElapsed, Canvas *p_canvas); //melakukan perubahan ketebalan canvas sesuai dengan waktu
        void setTopLeftPosition(Point p);
        
        bool getFlag(); //mengembalikan flag, true bila objek sudah berada di ujung layar
        void move(int dx, int dy);
        Point getTopLeftPosition();
        
        void setWidth(int width);
        void setHeight(int height);
        
        int getWidth();
        int getHeight();
    
    private : 
		void checkFlag(); //mengecek apakah objek berada di ujung layar
    
	private :
		Point topLeftPosition;
		Line line;
		int thickness;
        int direction; //1 up, 2 down
        int width;
        int height;
        static const double speed_x = .1;
        bool flag; //ni buat resolve masalah segmentation fault pas bullet dah nyampe ujung layar. flag=true pas nyampe di ujung layar
};

#endif
