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

tembakHancur :
	g++ core/canvas.cpp core/point.cpp transformasi/kincir.cpp perang-perangan/projectile.cpp perang-perangan/animation.cpp transformasi/TerjunPayung.cpp core/circle.cpp transformasi/tire.cpp transformasi/body.cpp pattern/polygon.cpp core/line.cpp pattern/pattern.cpp transformasi/helikopter.cpp transformasi/driverUtama.cpp -g -o bin/Hancur

kincir:
	g++ core/canvas.cpp core/point.cpp transformasi/kincir.cpp pattern/polygon.cpp core/line.cpp pattern/pattern.cpp transformasi/driverKincir.cpp -g -o bin/kincir

view:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp pattern/polygon.cpp pattern/pattern.cpp transformasi/helikopter.cpp transformasi/kincir.cpp transformasi/body.cpp transformasi/tire.cpp core/circle.cpp w2v/peta.cpp w2v/driver.cpp -o bin/w2v

peta:
	g++ -g core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp pattern/polygon.cpp pattern/pattern.cpp transformasi/helikopter.cpp transformasi/kincir.cpp transformasi/body.cpp transformasi/tire.cpp core/circle.cpp peta3d/driver.cpp peta3d/peta3d.cpp -o bin/peta
	
space:
	g++ core/canvas.cpp core/graphicsio.cpp core/line.cpp core/point.cpp pattern/polygon.cpp pattern/pattern.cpp colorpicker/rainbowPalette.cpp colorpicker/gradientPalette.cpp transformasi/TerjunPayung.cpp core/circle.cpp  transformasi/kincir.cpp transformasi/tire.cpp transformasi/body.cpp transformasi/helikopter.cpp cimbelSpace/bulletController.cpp cimbelSpace/bullet.cpp cimbelSpace/alienController.cpp cimbelSpace/driver.cpp  -g -o bin/cimbelSpace
