#include <string.h>
#include "agile_bit.h"

int agile_bit_get(const unsigned char* bits, int pos) {
	unsigned char mask;
	int i;
	mask = 0x80;
	for (i=0; i<(pos%8); ++i) mask >>= 1;
	return ((mask & bits[(int)(pos/8)]) == mask) ? 1 : 0;
}

void agile_bit_set(unsigned char* bits, int pos, int state) {
	unsigned char mask;
	int i;
	mask = 0x80;
	for (i=0; i<(pos%8); ++i) mask >>= 1;
	if (state)
		bits[pos/8] |= mask;
	else 
		bits[pos/8] &= ~mask;
}

void agile_bit_xor(const unsigned char* bits1, const unsigned char* bits2, unsigned char* bitsx, int size) {
	int i;
	for (i=0; i<size; ++i) {
		if (agile_bit_get(bits1, i) != agile_bit_get(bits2, i))
			agile_bit_set(bitsx, i, 1);
		else
			agile_bit_set(bitsx, i, 0);
	}
}

void bit_rot_left(unsigned char* bits, int size, int count) {
	int fbit;
	int lbit;
	int i,j;
	if (size > 0) {
		for (j=0; j<count; ++j) {
			for (i=0; i<=((size-1)/8); ++i) {
				lbit = agile_bit_get(&bit[i], 0);
				if (i==0) fbit = lbit;
				else agile_bit_set(&bits[i-1], 7, lbit);
				bits[i] <<= 1;
			}
			agile_bit_set(bits, size-1, fbit);
		}
	}
}

//////////////////////////////

void test_agile_bit() {

}

