debug-perang:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp perang-perangan/animation.cpp perang-perangan/kapal.cpp perang-perangan/pesawat.cpp perang-perangan/projectile.cpp perang-perangan/mainTest.cpp -g -o debug/perang

perang:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp perang-perangan/animation.cpp perang-perangan/kapal.cpp perang-perangan/pesawat.cpp perang-perangan/projectile.cpp perang-perangan/mainTest.cpp -o bin/perang

