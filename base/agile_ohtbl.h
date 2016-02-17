#ifndef agile_ohtbl_header
#define agile_ohtbl_header

#include <stdlib.h>

typedef struct agile_ohtbl_ {
	int positions;
	void* vacated;
	int (*h1)(const void* key);
	int (*h2)(const void* key);
	int (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);
	int size;
	void** table;
} agile_ohtbl;

int agile_ohtbl_init(agile_ohtbl* htbl, int positions, int (*h1)(const void*), int (*h2)(const void*),
	int (*match)(const void*,const void*), void (*destroy)(void*));
void agile_ohtbl_destroy(agile_ohtbl* htbl);
int agile_ohtbl_insert(agile_ohtbl* htbl, const void* data);
int agile_ohtbl_remove(agile_ohtbl* htbl, void** data);
int agile_ohtbl_lookup(agile_ohtbl* htbl, void** data);

#define agile_ohtbl_size(htbl) ((htbl)->size)

void test_agile_ohtbl();

#endif

