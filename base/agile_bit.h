#ifndef agile_bit_header
#define agile_bit_header

int agile_bit_get(const unsigned char* bits, int pos);
void agile_bit_set(unsigned char* bits, int pos, int state);
void agile_bit_xor(const unsigned char* bits1, const unsigned char* bits2, unsigned char* bitsx, int size);
void agile_bit_rot_left(unsigned char* bits, int size, int count);

void dump_bits(const unsigned char* bits, int size);
void test_agile_bit();

#endif
