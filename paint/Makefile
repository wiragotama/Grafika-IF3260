mouse: mouse_driver.cpp mouse.o rectangle_controller.o mouse_listener.o canvas.o line.o point.o
	g++ -g mouse_driver.cpp canvas.o mouse.o rectangle_controller.o  mouse_listener.o line.o point.o -lpthread -o mouse

mouse.o: mouse.h mouse.cpp
	g++ -g mouse.cpp -c

rectangle_controller.o: rectangle_controller.h rectangle_controller.cpp
	g++ -g rectangle_controller.cpp -c

mouse_listener.o: mouse_listener.h mouse_listener.cpp
	g++ -g mouse_listener.cpp -c

canvas.o: ../core/header.h ../core/canvas.h ../core/canvas.cpp
	g++ -g canvas.cpp -c

line.o: ../core/line.h ../core/line.cpp
	g++ -g ../core/line.cpp -c

point.o: ../core/point.h ../core/point.cpp
	g++ -g ../core/point.cpp -c