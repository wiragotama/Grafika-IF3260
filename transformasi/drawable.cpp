#include "drawable.h"
#include <algorithm>

bool isCollide(const Drawable& a, const Drawable& b) {
	Point tl_a = a.getPosition();
	Point br_a = Point(tl_a.getAbsis()+a.getWidth() , tl_a.getOrdinat()+a.getHeight());
	Point tl_b = b.getPosition();
	Point br_b = Point(tl_b.getAbsis()+b.getWidth() , tl_b.getOrdinat()+b.getHeight());

	Point tl_c = Point( std::max(tl_a.getAbsis(),tl_b.getAbsis()), std::max(tl_a.getOrdinat(),tl_b.getOrdinat()) );
	Point br_c = Point( std::min(br_a.getAbsis(),br_b.getAbsis()), std::min(br_a.getOrdinat(),br_b.getOrdinat()) );

	return !(br_c.getAbsis() < tl_c.getAbsis() || br_c.getOrdinat() < tl_c.getOrdinat());
}
