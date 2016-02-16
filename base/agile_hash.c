#include "agile_hash.h"

int agile_string_hash(const void* key) {
	const char* ptr;
	unsigned int val;
	val = 0;
	ptr = key;
	while (*ptr != '\0') {
		unsigned int tmp;
		val = (val << 4) + (*ptr);
		if ((tmp = (val & 0xf0000000))) {
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		++ptr;
	}
	return (int)val; // val % PRIME_TBLSIZ
}
