#include <limits.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "agile_compress.h"
#include "agile_bit.h"
#include "agile_pqueue.h"

static int compare_freq(const void* tree1, const void* tree2) {
	agile_huff_node* root1;
	agile_huff_node* root2;
	root1 = (agile_huff_node*)agile_bitree_data(agile_bitree_root((const agile_bitree*)tree1));
	root2 = (agile_huff_node*)agile_bitree_data(agile_bitree_root((const agile_bitree*)tree2));
	if (root1->freq < root2->freq) return 1;
	else if (root1->freq > root2->freq) return -1;
	else return 0;
}

// destroy tree from pqueue
static void destroy_tree(void* tree) {
	agile_bitree_destroy(tree);
	free(tree);
}

static int build_tree(int* freqs, agile_bitree** tree) {
	agile_bitree* init;
	agile_bitree* merge;
	agile_bitree* left;
	agile_bitree* right;
	agile_pqueue pqueue;
	agile_huff_node* data;
	int size, c;
	*tree = NULL;
	agile_pqueue_init(&pqueue, compare_freq, destroy_tree);
	for (c=0; c<=UCHAR_MAX; ++c) {
		if (freqs[c] != 0) {
			if ((init=(agile_bitree*)malloc(sizeof(agile_bitree)))==NULL) {
				agile_pqueue_destroy(&pqueue);
				return -1;
			}
			agile_bitree_init(init, free);
			if ((data=(agile_huff_node*)malloc(sizeof(agile_huff_node)))==NULL) {
				agile_pqueue_destroy(&pqueue);
				return -1;
			}
			data->symbol = c;
			data->freq = freqs[c];
			if (agile_bitree_ins_left(init, NULL, data) != 0) {
				free(data);
				agile_bitree_destroy(init);
				free(init);
				agile_pqueue_destroy(&pqueue);
				return -1;
			}
			if (agile_pqueue_insert(&pqueue, init) != 0) {
				agile_bitree_destroy(init);
				free(init);
				agile_pqueue_destroy(&pqueue);
				return -1;
			}
		}
	}
	size = agile_pqueue_size(&pqueue);
	for (c=1; c<=size-1; ++c) {
		if ((merge=(agile_bitree*)malloc(sizeof(agile_bitree)))==NULL) {
			agile_pqueue_destroy(&pqueue);
			return -1;
		}
		if (agile_pqueue_extract(&pqueue, (void**)&left) != 0) {
			agile_pqueue_destroy(&pqueue);
			free(merge);
			return -1;
		}
		if (agile_pqueue_extract(&pqueue, (void**)&right) != 0) {
			agile_pqueue_destroy(&pqueue);
			free(merge);
			return -1;
		}
		if ((data=(agile_huff_node*)malloc(sizeof(agile_huff_node)))==NULL) {
			agile_pqueue_destroy(&pqueue);
			free(merge);
			return -1;
		}
		memset(data, 0, sizeof(agile_huff_node));
		data->freq = ((agile_huff_node*)agile_bitree_data(agile_bitree_root(left)))->freq +
					 ((agile_huff_node*)agile_bitree_data(agile_bitree_root(right)))->freq;
		if (agile_bitree_merge(merge, left, right, data) != 0) {
			agile_pqueue_destroy(&pqueue);
			free(merge);
			return -1;
		}
		if (agile_pqueue_insert(&pqueue, merge) != 0) {
			agile_pqueue_destroy(&pqueue);
			agile_bitree_destroy(merge);
			free(merge);
			return -1;
		}
		free(left);
		free(right);
	}
	if (agile_pqueue_extract(&pqueue, (void**)tree) != 0) {
		agile_pqueue_destroy(&pqueue);
		return -1;
	}
	agile_pqueue_destroy(&pqueue);
	return 0;
}

static void build_table(agile_bitree_node* node, unsigned short code, unsigned char size, agile_huff_code* table) {
	if (!agile_bitree_is_eob(node)) {
		if (!agile_bitree_is_eob(agile_bitree_left(node))) {
			build_table(agile_bitree_left(node), code << 1, size + 1, table);
		}
		if (!agile_bitree_is_eob(agile_bitree_right(node))) {
			build_table(agile_bitree_right(node), (code << 1) | 0x0001, size + 1, table);
		}
		if (agile_bitree_is_eob(agile_bitree_left(node)) && agile_bitree_is_eob(agile_bitree_right(node))) {
			code = htons(code);
			table[((agile_huff_node*)agile_bitree_data(node))->symbol].used = 1;
			table[((agile_huff_node*)agile_bitree_data(node))->symbol].code = code;
			table[((agile_huff_node*)agile_bitree_data(node))->symbol].size = size;
		}
	}
}

int agile_huffman_compress(const unsigned char* original, unsigned char** compressed, int size) {
	agile_bitree* tree;
	agile_huff_code table[UCHAR_MAX + 1];
	int freqs[UCHAR_MAX + 1];
	int max, scale, hsize, ipos, opos, cpos, c, i;
	unsigned char* comp;
	unsigned char* temp;
	*compressed = NULL;
	for (c=0; c<=UCHAR_MAX; ++c) freqs[c] = 0;
	ipos = 0;
	if (size > 0) {
		while (ipos < size) {
			freqs[original[ipos]] += 1;
			ipos += 1;
		}
	}
	max = UCHAR_MAX;
	for (c=0; c<=UCHAR_MAX; ++c) {
		if (freqs[c] > max) max = freqs[c];
	} 
	for (c=0; c<=UCHAR_MAX; ++c) {
		scale = (int)(freqs[c] / ((double)max / (double)UCHAR_MAX));
		if (scale == 0 && freqs[c] != 0) freqs[c] = 1;
		else freqs[c] = scale;
	} 
	if (build_tree(freqs, &tree) != 0) return -1;
	for (c=0; c<=UCHAR_MAX; ++c) memset(&table[c], 0, sizeof(agile_huff_code));
	build_table(agile_bitree_root(tree), 0x0000, 0, table);
	agile_bitree_destroy(tree);
	free(tree);
	hsize = sizeof(int) + (UCHAR_MAX + 1);
	if ((comp = (unsigned char*)malloc(hsize)) == NULL) return -1;
	memcpy(comp, &size, sizeof(int));
	for (c=0; c<=UCHAR_MAX; ++c) comp[sizeof(int)+c] = (unsigned char)freqs[c];
	ipos = 0;
	opos = hsize * 8; // bit position
	while (ipos < size) {
		c = original[ipos];
		for (i=0; i<table[c].size; ++i) {
			if (opos % 8 == 0) {
				if ((temp = (unsigned char*)realloc(comp, (opos / 8) + 1)) == NULL) {
					free(comp);
					return -1;
				}
				comp = temp;
			}
			// unsigned in value = 0x1234
			// big endian:
			//		buf[1] : 0x34
			//		buf[0] : 0x12
			// little endian:
			//		buf[1] : 0x12
			//		buf[0] : 0x34
			cpos = (sizeof(short) * 8) - table[c].size + i; // see above comment to know why cpos is like this
			agile_bit_set(comp, opos, agile_bit_get((unsigned char*)&table[c].code, cpos));
			opos += 1;
		}
		ipos += 1;
	}
	*compressed = comp;
	return ((opos - 1) / 8) + 1;
}

int agile_huffman_uncompress(const unsigned char* compressed, unsigned char** original) {
	agile_bitree* tree;
	agile_bitree_node* node;
	int freqs[UCHAR_MAX + 1];
	int hsize, size, ipos, opos, state, c;
	unsigned char* orig;
	unsigned char* temp;
	*original = orig = NULL;
	hsize = sizeof(int) + (UCHAR_MAX + 1);
	memcpy(&size, compressed, sizeof(int));
	for (c=0; c<=UCHAR_MAX; ++c) freqs[c] = compressed[sizeof(int) + c];
	if (build_tree(freqs, &tree) != 0) return -1;
	ipos = hsize * 8;
	opos = 0;
	node = agile_bitree_root(tree);
	while (opos < size) {
		state = agile_bit_get(compressed, ipos);
		ipos += 1;
		if (state == 0) {
			// move to left
			if (agile_bitree_is_eob(node) || agile_bitree_is_eob(agile_bitree_left(node))) {
				agile_bitree_destroy(tree);
				free(tree);
				return -1;
			} else node = agile_bitree_left(node);
		} else {
			// move to right
			if (agile_bitree_is_eob(node) || agile_bitree_is_eob(agile_bitree_right(node))) {
				agile_bitree_destroy(tree);
				free(tree);
				return -1;
			} else node = agile_bitree_right(node);
		}
		if (agile_bitree_is_eob(agile_bitree_left(node)) && agile_bitree_is_eob(agile_bitree_right(node))) {
			if (opos > 0) {
				if ((temp = (unsigned char*)realloc(orig, opos + 1)) == NULL) {
					agile_bitree_destroy(tree);
					free(tree);
					free(orig);
					return -1;
				}
				orig = temp;
			} else {
				if ((orig = (unsigned char*)malloc(1)) == NULL) {
					agile_bitree_destroy(tree);
					free(tree);
					return -1;
				}
			}
			orig[opos] = ((agile_huff_node*)agile_bitree_data(node))->symbol;
			opos += 1;
			node = agile_bitree_root(tree);
		}
	}
	agile_bitree_destroy(tree);
	free(tree);
	*original = orig;
	return opos;
}

static int compare_win(const unsigned char* window, const unsigned char* buffer, int* offset, unsigned char* next) {
	int match, longest, i, j, k;
	*offset = 0;
	longest = 0;
	*next = buffer[0];
	for (k=0; k<LZ77_WINDOW_SIZE; ++k) { // sliding window
		i=k;
		j=0;
		match=0;
		while (i<LZ77_WINDOW_SIZE && j<LZ77_BUFFER_SIZE-1) { // check look-ahead buffer
			if (window[i] != buffer[j]) break;
			match += 1;
			i += 1;
			j += 1;
		}
		if (match > longest) {
			*offset = k;
			longest = match;
			*next = buffer[j];
		}
	}
	return longest;
}

int agile_lz77_compress(const unsigned char* original, unsigned char** compressed, int size) {

}

int agile_lz77_uncompress(const unsigned char* compressed, unsigned char** original) {

}

//////////////////////////////

const unsigned char TEST_STRING[] = "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf"
								    "aabcasl;dkfjas;lkdjfa;skdfjs;akdfjls;akdfjals;kdfj;lsakdf";

void test_agile_compress() {
	unsigned char* original = (unsigned char*)TEST_STRING;
	int origsize = sizeof(TEST_STRING);
	unsigned char* compressed;
	int compsize = agile_huffman_compress(original, &compressed, origsize);
	printf("origsize:%d, compsize:%d\n", origsize, compsize);
	unsigned char* original2;
	int origsize2 = agile_huffman_uncompress(compressed, &original2);
	printf("origsize2:%d, compare original and origsize2:%d\n", origsize2, strcmp((char*)original,(char*)original2));
	free(compressed);
	free(original2);
}
