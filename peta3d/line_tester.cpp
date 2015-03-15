#include "../core/header.h"
#include "../core/line.h"
#include "../core/point.h"

int main() {
	Line L1( Point(100, 0), Point(100, 100) ),
		L2( Point(50, 50), Point(250, 150) ),
		L3( Point(0, 0), Point(100, 0) ),
		L4( Point(50, 0), Point(50, 100) );

	Point* result12 = L1.getIntersectionPointWith(L2);
	result12->printInfo();
	cout << endl;

	Point* result34 = L3.getIntersectionPointWith(L4);
	result34->printInfo();
	cout << endl;

	free(result12);
	free(result34);

	return 0;
}
