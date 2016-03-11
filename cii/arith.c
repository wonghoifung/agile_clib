/* includes */
#include "arith.h"

/* data */

/* prototypes */

/* functions */
int Arith_max(int x, int y) {
	return x > y ? x : y;
}

int Arith_min(int x, int y) {
	return x > y ? y : x;
}

// Arith_div(x,y) is the maximum integer 
// that does not exceed the real number
// z such that z*y=x
// eg, -13/5=-3
int Arith_div(int x, int y) {
	/* division truncates toward 0 &&
	x and y have different signs && */
	if ((-13 / 5 == -2) && 
		((x < 0) != (y < 0)) &&
		(x % y != 0)) {
		return x / y - 1;
	} else {
		return x / y;
	}
}

int Arith_mod(int x, int y) {
	return x - y * Arith_div(x, y);
	// if ((-13 / 5 == -2) && 
	// 	((x < 0) != (y < 0)) &&
	// 	(x % y != 0)) {
	// 	return x % y + y;
	// } else {
	// 	return x % y;
	// }
}

int Arith_floor(int x, int y) {
	return Arith_div(x, y);
}

int Arith_ceiling(int x, int y) {
	return Arith_div(x, y) + (x % y != 0);
}
