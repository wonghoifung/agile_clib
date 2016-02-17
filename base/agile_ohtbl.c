#include <string.h>
#include "agile_ohtbl.h"

static char vacated;

int agile_ohtbl_init(agile_ohtbl* htbl, int positions, int (*h1)(const void*), int (*h2)(const void*),
	int (*match)(const void*,const void*), void (*destroy)(void*)) {
	int i;
	if ((htbl->table=(void**)malloc(positions*sizeof(void*)))==NULL) return -1;
	htbl->positions = positions;
	for (i=0; i<htbl->positions; ++i) htbl->table[i] = NULL;
	htbl->vacated = &vacated;
	htbl->h1 = h1;
	htbl->h2 = h2;
	htbl->match = match;
	htbl->destroy = destroy;
	htbl->size = 0;
	return 0;
}

void agile_ohtbl_destroy(agile_ohtbl* htbl) {
	int i;
	if (htbl->destroy!=NULL) {
		for (i=0; i<htbl->positions; ++i) {
			if (htbl->table[i]!=NULL && htbl->table[i]!=htbl->vacated)
				htbl->destroy(htbl->table[i]);
		}
	}
	free(htbl->table);
	memset(htbl, 0, sizeof(agile_ohtbl));
}

int agile_ohtbl_insert(agile_ohtbl* htbl, const void* data) {
	void* temp;
	int position;
	int i;
	if (htbl->size==htbl->positions) return -1;
	temp = (void*)data;
	if (agile_ohtbl_lookup(htbl, &temp)==0) {
		return 1;
	}
	for (i=0; i<htbl->positions; ++i) {
		position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
		if (htbl->table[position]==NULL || htbl->table[position]==htbl->vacated) {
			//printf("-----insert %s pos:%d i:%d\n", (char*)data, position, i);
			htbl->table[position] = (void*)data;
			htbl->size += 1;
			return 0;
		}
	}
	return -1;
}

int agile_ohtbl_remove(agile_ohtbl* htbl, void** data) {
	int position;
	int i;
	for (i=0; i<htbl->positions; ++i) {
		position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
		if (htbl->table[position]==NULL) return -1;
		else if (htbl->table[position]==htbl->vacated) continue;
		else if (htbl->match(htbl->table[position], *data)) {
			*data = htbl->table[position];
			htbl->table[position] = htbl->vacated;
			htbl->size -= 1;
			return 0;
		}
	}
	return -1;
}

int agile_ohtbl_lookup(agile_ohtbl* htbl, void** data) {
	int position;
	int i;
	for (i=0; i<htbl->positions; ++i) {
		position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
		//printf("-----check %s at pos:%d i:%d\n", (char*)*data, position, i);
		if (htbl->table[position]==NULL) return -1;
		else if (htbl->table[position]==htbl->vacated) continue;
		else if (htbl->match(htbl->table[position], *data)) {
			*data = htbl->table[position];
			return 0;
		}
	}
	return -1;
}

//////////////////////////////

#include "test_common.h"
#include "agile_hash.h"

static int agile_string_hash2(const void* key) {
	int h1 = agile_string_hash(key);
	return h1+1;
}

void test_agile_ohtbl() {
	agile_ohtbl htbl;
	agile_ohtbl_init(&htbl, 100, agile_string_hash, agile_string_hash2, string_match, free);

	char* d1 = get_data(1);
	printf("insert d1 %d\n", agile_ohtbl_insert(&htbl, (void*)d1));
	char* d2 = get_data(2);
	printf("insert d2 %d\n", agile_ohtbl_insert(&htbl, (void*)d2));
	char* d3 = get_data(3);
	printf("insert d3 %d\n", agile_ohtbl_insert(&htbl, (void*)d3));
	char* d4 = get_data(4);
	printf("insert d4 %d\n", agile_ohtbl_insert(&htbl, (void*)d4));

	printf("size %d\n", agile_ohtbl_size(&htbl));
	printf("lookup d1 %d\n", agile_ohtbl_lookup(&htbl,(void**)&d1));
	printf("lookup d2 %d\n", agile_ohtbl_lookup(&htbl,(void**)&d2));
	printf("lookup d3 %d\n", agile_ohtbl_lookup(&htbl,(void**)&d3));
	printf("lookup d4 %d\n", agile_ohtbl_lookup(&htbl,(void**)&d4));
	void* vd2 = (void*)d2;
	if (agile_ohtbl_remove(&htbl, &vd2)==0) free(vd2);
	printf("size %d\n", agile_ohtbl_size(&htbl));
	printf("lookup d1 %d\n", agile_ohtbl_lookup(&htbl,(void**)&d1));
	printf("lookup d2 %d\n", agile_ohtbl_lookup(&htbl,(void**)&d2));
	printf("lookup d3 %d\n", agile_ohtbl_lookup(&htbl,(void**)&d3));
	printf("lookup d4 %d\n", agile_ohtbl_lookup(&htbl,(void**)&d4));

	agile_ohtbl_destroy(&htbl);
}
