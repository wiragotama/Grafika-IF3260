/* File : Point1.h */
/* Author : 13512015 - Jan Wira Gotama Putra */
#include "point.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(int new_x, int new_y) {
	x = new_x;
	y = new_y;
}

Point::Point(const Point& p) {
	x = p.x;
	y = p.y;
}

Point& Point::operator=(const Point& p) {
	setAbsis(p.x);
	setOrdinat(p.y);
	return *this;
}

Point::~Point() {
}

void Point::printInfo() {
    printf("(%d, %d)", getAbsis(), getOrdinat());
}

void Point::rotate(double angle, int rx, int ry) {
    int x1 = cos(angle)*(x-rx)-sin(angle)*(y-ry)+rx,
        y1 = sin(angle)*(x-rx)+cos(angle)*(y-ry)+ry;
    x = x1;
    y = y1;
}

int Point::getAbsis() {
	return x;
}

int Point::getOrdinat() {
	return y;
}

void Point::setAbsis(int x) {
	this->x = x;
}

void Point::setOrdinat(int y) {
	this->y = y;
}

void Point::moveRight(int d) {
	x+=d;
}

void Point::moveLeft(int d) {
	x-=d;
}

void Point::moveUp(int d) {
	y-=d;
}

void Point::moveDown(int d) {
	y+=d;
}

void Point::move(int dx, int dy) {
	x+=dx;
	y+=dy;
}

