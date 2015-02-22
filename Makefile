debug-perang:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp perang-perangan/animation.cpp perang-perangan/kapal.cpp perang-perangan/pesawat.cpp perang-perangan/projectile.cpp perang-perangan/mainTest.cpp -g -o debug/perang

perang:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp perang-perangan/animation.cpp perang-perangan/kapal.cpp perang-perangan/pesawat.cpp perang-perangan/projectile.cpp perang-perangan/mainTest.cpp -o bin/perang

picker:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp colorpicker/gradientPalette.cpp colorpicker/grafika.cpp colorpicker/rainbowPalette.cpp -o bin/picker
	
poly:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp pattern/polygon.cpp pattern/pattern.cpp pattern/driver.cpp -o bin/poly

transformation:
	g++ core/canvas.cpp core/circle.cpp core/line.cpp core/point.cpp transformasi/TerjunPayung.cpp transformasi/driver.cpp -o bin/transformasi

tire :
	g++ core/canvas.cpp core/circle.cpp core/point.cpp transformasi/tire.cpp transformasi/driverTire.cpp -o bin/tireTest
	
body :
	g++ core/canvas.cpp core/point.cpp transformasi/body.cpp pattern/polygon.cpp core/line.cpp pattern/pattern.cpp transformasi/driverBody.cpp -g -o bin/bodyTest
