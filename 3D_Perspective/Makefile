cube.o: cube.cpp cube.h
	g++ -g -c cube.cpp

camera3d.o: camera3d.cpp camera3d.h
	g++ -g -c camera3d.cpp

matrix.o: matrix.cpp matrix.h
	g++ -g -c matrix.cpp

point3D.o: point3D.cpp point3D.h
	g++ -g -c point3D.cpp

globals.o: globals.cpp globals.h
	g++ -g -c globals.cpp
	
point.o: point.cpp point.h
	g++ -g -c point.cpp
	
line.o: line.cpp line.h
	g++ -g -c line.cpp
	
polygon.o: polygon.cpp polygon.h
	g++ -g -c polygon.cpp
	
canvas.o: canvas.cpp canvas.h
	g++ -g -c canvas.cpp

graphicsio.o: graphicsio.cpp graphicsio.h
	g++ -g -c graphicsio.cpp
	
circle.o: circle.cpp circle.h
	g++ -g -c circle.cpp
	
fill: point.o line.o polygon.o canvas.o circle.o fill_driver.cpp
	g++ -g fill_driver.cpp point.o line.o polygon.o canvas.o circle.o -o fill

cube3d: cube.o camera3d.o matrix.o point3D.o globals.o point.o line.o polygon.o canvas.o graphicsio.o cube3d_driver.cpp
	g++ -g cube3d_driver.cpp cube.o camera3d.o matrix.o point3D.o globals.o point.o \
	line.o polygon.o canvas.o graphicsio.o -o cube3d

clean:
	rm *.o *~ cube3d
