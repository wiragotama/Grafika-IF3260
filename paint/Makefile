mouse: mouse_driver.cpp mouse.o rectangle_controller.o mouse_listener.o
	g++ -g mouse_driver.cpp mouse.o rectangle_controller.o  mouse_listener.o -lpthread -o mouse

mouse.o: mouse.h mouse.cpp
	g++ -g mouse.cpp -c

rectangle_controller.o: rectangle_controller.h rectangle_controller.cpp
	g++ -g rectangle_controller.cpp -c

mouse_listener.o: mouse_listener.h mouse_listener.cpp
	g++ -g mouse_listener.o -c
