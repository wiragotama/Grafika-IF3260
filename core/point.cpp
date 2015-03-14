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

bool Point::isOrigin() const {
	return (this->getAbsis() == 0) && (this->getOrdinat() == 0);
}

void Point::rotate(double angle, int rx, int ry) {
    int x1 = cos(angle)*(x-rx)-sin(angle)*(y-ry)+rx,
        y1 = sin(angle)*(x-rx)+cos(angle)*(y-ry)+ry;
    x = x1;
    y = y1;
}

int Point::getAbsis() const {
	return x;
}

int Point::getOrdinat() const {
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

int Point::orientation(Point p, Point q, Point r) {
    // See 10th slides from following link for derivation of the formula
    // http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
    int val = (q.getOrdinat() - p.getOrdinat()) * (r.getAbsis() - q.getAbsis()) -
              (q.getAbsis() - p.getAbsis()) * (r.getOrdinat() - q.getOrdinat()); // cross products
 
    if (val == 0) return 0;  // colinear
 
    return (val > 0)? 1: 2; // clock or counterclock wise // jadi intinya terbalik 
}

bool Point::pointGreaterThan(Point a, Point b){
	if(b.getAbsis() != a.getAbsis())
		return a.getAbsis() < b.getAbsis();
	else
		return a.getOrdinat() > b.getOrdinat();
}
