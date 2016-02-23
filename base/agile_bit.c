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
				lbit = agile_bit_get(&bits[i], 0);
				if (i==0) fbit = lbit;
				else agile_bit_set(&bits[i-1], 7, lbit);
				bits[i] <<= 1;
			}
			agile_bit_set(bits, size-1, fbit);
		}
	}
}

//////////////////////////////

#include <stdio.h>

void dump_bits(const unsigned char* bits, int size) {
	int bit;
	for (int i=0; i<size; ++i) {
		bit = agile_bit_get(bits, i);
		if (i/8>0 && i%8==0) printf(" %d", bit);
		else printf("%d", bit); 
	}
	printf("\n");
}

void test_agile_bit() {
	unsigned char bits[4] = {0};
	int size = 32;
	dump_bits(bits, size);
	agile_bit_set(bits, 7, 1);
	agile_bit_set(bits, 9, 1);
	dump_bits(bits, size);
	bit_rot_left(bits, size, 7);
	dump_bits(bits, size);
	printf("bit2: %d\n", agile_bit_get(bits, 2));
}

