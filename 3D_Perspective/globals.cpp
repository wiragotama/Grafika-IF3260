#include "globals.h"

const double GRAFIKA_EPSILON = 1.0e-6;

bool GRAFIKA_isClose(double a, double b) {
	return abs(a-b) < GRAFIKA_EPSILON;
}
