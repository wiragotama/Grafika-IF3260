debug-perang:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp perang-perangan/mainTest.cpp -g -o debug/perang

perang:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp perang-perangan/mainTest.cpp -o bin/perang

