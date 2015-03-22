cube.o: cube.cpp
	g++ -c cube.cpp

camera3d.o: camera3d.cpp
	g++ -c camera3d.cpp

matrix.o: matrix.cpp
	g++ -c matrix.cpp

point3D.o: point3D.cpp
	g++ -c point3D.cpp

globals.o: globals.cpp
	g++ -c globals.cpp
	
point.o: point.cpp point.h
	g++ -c point.cpp
	
line.o: line.cpp line.h
	g++ -c line.cpp
	
polygon.o: polygon.cpp polygon.h
	g++ -c polygon.cpp
	
canvas.o: canvas.cpp canvas.h
	g++ -c canvas.cpp
	
cube3d_driver.o: cube3d_driver.cpp
	g++ -c cube3d_driver.cpp

cube3d: cube.o camera3d.o matrix.o point3D.o globals.o point.o line.o polygon.o canvas.o cube3d_driver.o
	g++ -g cube.o camera3d.o matrix.o point3D.o globals.o point.o line.o polygon.o canvas.o cube3d_driver.o -o cube3d

clean:
	\rm *.o *~ cube3d
