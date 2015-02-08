#include "animation.h"
#include <algorithm>

void Animation::setTopLeftPosition(int x, int y) {
	topLeftPosition.setAbsis(x);
	topLeftPosition.setOrdinat(y);
}

void Animation::setWidth(int width) {
	this->width = width;
}

void Animation::setHeight(int height) {
	this->height = height;
}

bool Animation::isCollide(const Animation& other) {
	Point tl_a = getTopLeftPosition(), br_a = getBottomRight();
	Point tl_b = other.getTopLeftPosition(), br_b = other.getBottomRight();

	Point tl_c = Point( std::max(tl_a.getAbsis(),tl_b.getAbsis()), std::max(tl_a.getOrdinat(),tl_b.getOrdinat()) );
	Point br_c = Point( std::min(br_a.getAbsis(),br_b.getAbsis()), std::min(br_a.getOrdinat(),br_b.getOrdinat()) );

	return !(br_c.getAbsis() < tl_c.getAbsis() || br_c.getOrdinat() < tl_c.getOrdinat());
}

Point Animation::getTopLeftPosition() const {
	return topLeftPosition;
}

Point Animation::getBottomRight() const {
	Point tl = getTopLeftPosition();
	return Point(tl.getAbsis()+width, tl.getOrdinat()+height);
}

void Animation::setTopLeftPosition(Point p){
	topLeftPosition = p;
}
