#ifndef agile_compress_header
#define agile_compress_header

#include "agile_bitree.h"

typedef struct agile_huff_node_ {
	unsigned char symbol;
	int freq;
} agile_huff_node;

typedef struct agile_huff_code_ {
	unsigned char used;
	unsigned short code;
	unsigned char size;
} agile_huff_code;

// for token members
#define LZ77_TYPE_BITS 1
#define LZ77_WINOFF_BITS 12
#define LZ77_BUFLEN_BITS 5
#define LZ77_NEXT_BITS 8

// for sliding window
#define LZ77_WINDOW_SIZE 4096
// for look-ahead buffer
#define LZ77_BUFFER_SIZE 32

// for phrase tokens
#define LZ77_PHRASE_BITS (LZ77_TYPE_BITS+LZ77_WINOFF_BITS+LZ77_NEXT_BITS+LZ77_BUFLEN_BITS)

// for symbol tokens
#define LZ77_SYMBOL_BITS (LZ77_TYPE_BITS+LZ77_NEXT_BITS)

int agile_huffman_compress(const unsigned char* original, unsigned char** compressed, int size);
int agile_huffman_uncompress(const unsigned char* compressed, unsigned char** original);

int agile_lz77_compress(const unsigned char* original, unsigned char** compressed, int size);
int agile_lz77_uncompress(const unsigned char* compressed, unsigned char** original);

void test_agile_compress();

#endif
