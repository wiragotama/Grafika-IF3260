# mouse: mouse_driver.cpp mouse.o rectangle_controller.o mouse_listener.o canvas.o line.o point.o
# 	g++ -g mouse_driver.cpp canvas.o mouse.o rectangle_controller.o  mouse_listener.o line.o point.o -lpthread -o mouse

# mouse.o: mouse.h mouse.cpp
# 	g++ -g mouse.cpp -c

# rectangle_controller.o: rectangle_controller.h rectangle_controller.cpp
# 	g++ -g rectangle_controller.cpp -c

# mouse_listener.o: mouse_listener.h mouse_listener.cpp
# 	g++ -g mouse_listener.cpp -c

# canvas.o: ../3D_Perspective/canvas.h ../3D_Perspective/canvas.cpp
# 	g++ -g ../3D_Perspective/canvas.cpp -c

# line.o: ../3D_Perspective/line.h ../3D_Perspective/line.cpp
# 	g++ -g ../3D_Perspective/line.cpp -c

# point.o: ../3D_Perspective/point.h ../3D_Perspective/point.cpp
# 	g++ -g ../3D_Perspective/point.cpp -c

mouse: 
	g++ -o mouse ../core/graphicsio.cpp mouse_driver.cpp mouse_listener.cpp circle_controller.cpp rectangle_controller.cpp triangle_controller.cpp ../3D_Perspective/canvas.cpp ../3D_Perspective/polygon.cpp ../3D_Perspective/circle.cpp ../3D_Perspective/line.cpp ../3D_Perspective/point.cpp mouse.cpp -lpthread
