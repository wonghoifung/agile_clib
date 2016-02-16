#ifndef agile_chtbl_header
#define agile_chtbl_header

#include <stdlib.h>
#include "agile_list.h"

typedef struct agile_chtbl_ {
	int buckets;
	int (*h)(const void* key);
	int (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);
	int size;
	agile_list* table;
} agile_chtbl;

int agile_chtbl_init(agile_chtbl* htbl, int buckets, int(*h)(const void*), 
	int(*match)(const void*,const void*), void(*destroy)(void*));
void agile_chtbl_destroy(agile_chtbl* htbl);
int agile_chtbl_insert(agile_chtbl* htbl, const void* data);
int agile_chtbl_remove(agile_chtbl* htbl, void** data);
int agile_chtbl_lookup(const agile_chtbl* htbl, void** data);

#define agile_chtbl_size(htbl) ((htbl)->size)

void test_agile_chtbl();

#endif

