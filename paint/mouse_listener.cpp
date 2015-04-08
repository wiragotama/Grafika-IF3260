#include "mouse_listener.h"

MouseListener::MouseListener() {}
MouseListener::MouseListener(const MouseListener&) {}
MouseListener& MouseListener::operator= (const MouseListener&) {}
MouseListener::~MouseListener() {}

void MouseListener::leftDown(int, int) {}
void MouseListener::leftUp(int, int) {}
void MouseListener::rightDown(int, int) {}
void MouseListener::rightUp(int, int) {}
void MouseListener::middleDown(int, int) {}
void MouseListener::middleUp(int, int) {}
void MouseListener::movement(int, int) {}
