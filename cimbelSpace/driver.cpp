#include "../core/header.h"
#include "../core/graphicsio.h"
#include "../core/canvas.h"
#include "../colorpicker/rainbowPalette.h"
#include "../colorpicker/gradientPalette.h"
#include "../transformasi/helikopter.h"
#include "../transformasi/drawable.h"
#include "../perang-perangan/animation.h"
#include "../perang-perangan/projectile.h"
#include "../transformasi/TerjunPayung.h"
#include "../cimbelSpace/bulletController.h"
#include "../cimbelSpace/alienController.h"
#include <ctime>

void gameIntroduction(Helikopter* helikopter, Canvas* canvas);
void showRainbowPalette(Helikopter* helikopter, Canvas* canvas);
void gamePlay(Helikopter* helikopter, Canvas *canvas);
void keyHandle(char c, BulletController* bulletController, Helikopter *helikopter);
void cleanUp(BulletController* bulletController, AlienController *alienController);
bool planeCrash(AlienController *alienController, Helikopter* helikopter);

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r) {
    if (q.getAbsis() <= max(p.getAbsis(), r.getAbsis()) && q.getAbsis() >= min(p.getAbsis(), r.getAbsis()) &&
        q.getOrdinat() <= max(p.getOrdinat(), r.getOrdinat()) && q.getOrdinat() >= min(p.getOrdinat(), r.getOrdinat()))
       return true;
 
    return false;
}
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) {
	// yang membentuk line = p dan q
    // See 10th slides from following link for derivation of the formula
    // http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
    int val = (q.getOrdinat() - p.getOrdinat()) * (r.getAbsis() - q.getAbsis()) -
              (q.getAbsis() - p.getAbsis()) * (r.getOrdinat() - q.getOrdinat()); //ini cross product
 
    if (val == 0) return 0;  // colinear
 
    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool ccw (Point p, Point q, Point r) {
	return (orientation(p,q,r) == 2);
}
 
// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
}

Point intersection(Point p1, Point p2, Point p3, Point p4) {
	// asumsi ketika panggil method ini uda pasti terjadi intersection
	// Store the values for fast access and easy
	// equations-to-code conversion
	int x1 = p1.getAbsis(), x2 = p2.getAbsis(), x3 = p3.getAbsis(), x4 = p4.getAbsis();
	int y1 = p1.getOrdinat(), y2 = p2.getOrdinat(), y3 = p3.getOrdinat(), y4 = p4.getOrdinat();

	// mengubah bentuk jadi Ax+By = C
	// persamaan umum: -x(y2-y1) + y(x2-x1) = y1(x2-x1) - x1(y2-y1)
	// jadi x(y1-y2) + y(x2-x1) = y1(x2-x1)+x1(y1-y2)
	// jadi A = y1-y2, B = x2-x1, C = A.x1 + B.y1
	int A1 = y1 - y2;
	int B1 = x2 - x1;
	int C1 = A1 * x1 + B1 * y1;

	int A2 = y3 - y4;
	int B2 = x4 - x3;
	int C2 = A2 * x3 + B2 * y3;

	int det = A1 * B2 - A2 * B1;
	int xnew = (B2*C1 - B1*C2)/det;
    int ynew = (A1 * C2 - A2 * C1) / det;
	Point ret(xnew,ynew);
	return ret;
}

double angle(Point a, Point o, Point b) {
	// a.printInfo();
	// o.printInfo();
	// b.printInfo();
	Line l1(a,o);
	Line l2(o,b);
	float length1 = l1.getLength();
	float length2 = l2.getLength();
	int tmp = l1.getDifXInVector() * l2.getDifXInVector() + l1.getDifYInVector() * l2.getDifYInVector();
	// cout << tmp << " " << length1 << " " << length2 << " haha" << endl;
	double haha = 0;
	if (length1 == 0 || length2 == 0) { //berarti point tersebut sama
		haha = 1; //biar di acos jadi 0;
	} else {
		haha = (double)tmp/(length1 * length2);
		if (haha > 1.0) haha = 1.0;
		else if (haha < -1.0) haha = -1.0;
	}
	// cout << "haha " << haha << endl;
	// getchar();
	return acos(haha); //return dalam radian
}

int main() {
	Canvas canvas;
	Polygon poly;
	poly.addPoint(Point(0,0));
	poly.addPoint(Point(100,0));
	poly.addPoint(Point(100,100));
	poly.addPoint(Point(0,100));
	poly.addPoint(Point(0,0));
	poly.draw(&canvas, canvas.pixel_color(255,0,0));
	canvas.flush();

	vector<Point> edges = poly.getPoints();
	int x, y;
	cin >> x >> y;
	Point ptemp1(x,y);
	double sum = 0;
	for (int p = 0; p < edges.size()-1; ++p){ //ingat ganti p
		float temp = 0.0f;
		if (ccw(edges[p], edges[p+1],ptemp1)) {
			temp = angle(edges[p], ptemp1, edges[p+1]);
			sum += temp;
		} else {
			temp -= angle(edges[p], ptemp1, edges[p+1]);
			sum -= temp;
		}
		// edges[p].printInfo();
		// edges[p+1].printInfo();
		// cout << "sum " << sum << " temp " << temp << endl;
	}

	// cout << sum << endl;

	bool inPolygon = (fabs(fabs(sum) - 2*M_PI) < 0.000001);
	cout << "di dalam polygon ga? " << inPolygon << endl;
	Point topLeftPosition(540,400);
	Helikopter helikopter(topLeftPosition);
	
	gameIntroduction(&helikopter, &canvas);
	gamePlay(&helikopter, &canvas);

	return 0;
}

void showRainbowPalette(Helikopter* helikopter, Canvas* canvas) {
	
	char c;
	string msgPalette = "Rainbow palette";
	string msgGradient = "Gradient palette (your choise)";
	
	GraphicsIO graphicsIO;
	
	int x_offset = (canvas->get_vinfo().xres - COLORTABLE_WIDTH*COLORTABLE_CELLSIZE)/5;
	int x_offset0 = x_offset + COLORTABLE_WIDTH*COLORTABLE_CELLSIZE + 100;
	int y_offset = (canvas->get_vinfo().yres - COLORTABLE_HEIGHT*COLORTABLE_CELLSIZE)/2 - 50;
	
	RainbowPalette rainbowPalette(x_offset, y_offset);
	GradientPalette gradientPalette(x_offset0, y_offset);
	
	rainbowPalette.initRainbowColor(canvas);
	do {
		system("clear");
		rainbowPalette.drawPalette(canvas);
		rainbowPalette.drawCursor(canvas);
		
		canvas->flush();
		rainbowPalette.drawPalette(canvas);
		rainbowPalette.drawCursor(canvas);
		gradientPalette.drawColorGradient(canvas->getColor(rainbowPalette.getScreenX(),rainbowPalette.getScreenY()), canvas);
		gradientPalette.drawCursor(canvas);
		
		helikopter->setColor(gradientPalette.getColorTable(gradientPalette.getCursorX(), gradientPalette.getCursorY()));
		//helikopter->setColor(canvas->getColor(gradientPalette.getScreenX(), gradientPalette.getScreenY()));
		helikopter->draw(canvas, helikopter->getColor());
		canvas->flush();
		
		canvas->putColorInfo(rainbowPalette.getScreenX(), rainbowPalette.getScreenY(), msgPalette.c_str());
		canvas->putColorInfo(gradientPalette.getScreenX(), gradientPalette.getScreenY(), msgGradient.c_str());
		
		c = graphicsIO.getch();
		rainbowPalette.moveCursor(c);
		gradientPalette.moveCursor(c);
		
	} while (c!='\n');
}

void gameIntroduction(Helikopter* helikopter, Canvas* canvas) {
	system("clear");
	printf("Suatu ketika... \n");
	printf("perang intergalaxy terbesar terjadi di galaxy cimbelSakti...\n");
	printf("--- Tim cimbelExtension --- \n");
	printf("menciptakan pesawat terhebat untuk menangkan perang tersebut...\n");
	printf("Anda TERPILIH untuk menjadi pilot dari pesawat hebat tersebut...\n");
	getchar();
	showRainbowPalette(helikopter, canvas);
	canvas->clearScreen();
}

void gamePlay(Helikopter* helikopter, Canvas *canvas) {
	
	BulletController bulletController;
	AlienController alienController;
	
	GraphicsIO graphicsIO;
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_ENABLE);
	
	char c;
	int timeCounter = 0;
	bool planeBroke = false;
	do {
		srand(time(NULL));
		int rand_var = rand()%640 + 1; //posisi random spawn monster
		if (timeCounter==200) {
			//spawn monster
			Point ATLP(rand_var, 1);
			alienController.addAlien(ATLP);
			timeCounter = 0;
		}
		
		bulletController.draw(canvas, canvas->pixel_color(0,0,255));
		alienController.draw(canvas, canvas->pixel_color(218,165,32));
		helikopter->draw(canvas, helikopter->getColor());
		
		canvas->flush();
		
		int i = GraphicsIO::kbhit();
		if (i!=0) {
			c = fgetc(stdin);
			keyHandle(c, &bulletController, helikopter);
		}
		bulletController.move(0, -2);
		alienController.move(0, 2);
		//bersih2
		planeBroke = planeCrash(&alienController, helikopter);
		cleanUp(&bulletController, &alienController);
		timeCounter++;
		
	} while (c!='\n' && !planeBroke);
	helikopter->draw(canvas, helikopter->getColor());
	canvas->flush();
	GraphicsIO::nonblock(GraphicsIO::NONBLOCK_DISABLE);
}

void keyHandle(char c, BulletController* bulletController, Helikopter *helikopter) {
	if (c=='f') {
		Point TLP(helikopter->getTopLeftPosition().getAbsis(), helikopter->getTopLeftPosition().getOrdinat()-11);
		bulletController->addBullet(TLP, 1);
	}
	else if (c == 97 && helikopter->getTopLeftPosition().getAbsis() > 0) { //left gradient
		helikopter->move(-2, 0);
	}
	else if (c == 100 && helikopter->getTopLeftPosition().getAbsis() + helikopter->getWidth() < 640) { //right gradient
		helikopter->move(2, 0);
	}
}

void cleanUp(BulletController* bulletController, AlienController *alienController) {
	if (alienController->getSize() > 0) {
		for (int i=0; i<bulletController->getSize();) {
			Point BRP(bulletController->getBullet(i).getTopLeftPosition().getAbsis() + bulletController->getBullet(i).getWidth(), 
					bulletController->getBullet(i).getTopLeftPosition().getOrdinat() + bulletController->getBullet(i).getHeight());
			bool flag = alienController->crashDelete(bulletController->getBullet(i).getTopLeftPosition(), BRP);
			if (flag) {
				bulletController->deleteBullet(i);
			}
			else i++;
		}
	}
	alienController->garbageCollector();
	bulletController->garbageCollector();
}

bool planeCrash(AlienController *alienController, Helikopter* helikopter) {
	bool flag = false;
	for (int i=0; i<!flag && alienController->getSize(); ) {
		Point BRP(helikopter->getTopLeftPosition().getAbsis() + helikopter->getWidth(), 
				helikopter->getTopLeftPosition().getOrdinat() + helikopter->getHeight());
		flag = alienController->crashDelete(helikopter->getTopLeftPosition(), BRP);
		if (flag) {
			helikopter->brokeBody();
		}
		else i++;
	}
	return flag;
}
