#include <string.h>
#include "agile_chtbl.h"

int agile_chtbl_init(agile_chtbl* htbl, int buckets, int(*h)(const void*), 
	int(*match)(const void*,const void*), void(*destroy)(void*)) {
	int i;
	if ((htbl->table=(agile_list*)malloc(buckets*sizeof(agile_list)))==NULL) return -1;
	htbl->buckets = buckets;
	for (i = 0; i < buckets; ++i) {
		agile_list_init(&htbl->table[i], destroy);
	}
	htbl->h = h;
	htbl->match = match;
	htbl->destroy = destroy;
	htbl->size = 0;
	return 0;
}

void agile_chtbl_destroy(agile_chtbl* htbl) {
	int i;
	for (i=0; i<htbl->buckets; ++i) {
		agile_list_destroy(&htbl->table[i]);
	}
	free(htbl->table);
	memset(htbl, 0, sizeof(agile_chtbl));
}

int agile_chtbl_insert(agile_chtbl* htbl, const void* data) {
	void* temp;
	int bucket;
	int retval;

	temp = (void*)data;
	if (agile_chtbl_lookup(htbl, &temp)==0) return 1;

	bucket = htbl->h(data) % htbl->buckets;

	if ((retval = agile_list_ins_next(&htbl->table[bucket],NULL,data))==0) htbl->size += 1;
	return retval;
}

int agile_chtbl_remove(agile_chtbl* htbl, void** data) {
	agile_list_element* element;
	agile_list_element* prev;
	int bucket;
	bucket = htbl->h(*data) % htbl->buckets;

	prev = NULL;

	for (element=agile_list_head(&htbl->table[bucket]); element!=NULL; element=agile_list_next(element)) {
		if (htbl->match(*data, agile_list_data(element))) {
			if (agile_list_rem_next(&htbl->table[bucket], prev, data)==0) {
				htbl->size -= 1;
				return 0;
			} else {
				return -1;
			}
		}
		prev = element;
	}
	return -1;
}

int agile_chtbl_lookup(const agile_chtbl* htbl, void** data) {
	agile_list_element* element;
	int bucket;
	bucket = htbl->h(*data) % htbl->buckets;
	for (element=agile_list_head(&htbl->table[bucket]); element!=NULL; element=agile_list_next(element)) {
		if (htbl->match(*data, agile_list_data(element))) {
			*data = agile_list_data(element);
			return 0;
		}
	}
	return -1;
}

//////////////////////////////

#include "test_common.h"
#include "agile_hash.h"

void test_agile_chtbl() {
	agile_chtbl htbl;
	agile_chtbl_init(&htbl, 10, agile_string_hash, string_match, free);

	char* data1 = get_data(1);
	agile_chtbl_insert(&htbl, data1);
	char* data2 = get_data(2);
	agile_chtbl_insert(&htbl, data2);
	char* data3 = get_data(3);
	agile_chtbl_insert(&htbl, data3);

	printf("lookup data2: %d\n", agile_chtbl_lookup(&htbl,(void**)&data2));
	agile_chtbl_remove(&htbl,(void**)&data2);
	printf("lookup data2: %d\n", agile_chtbl_lookup(&htbl,(void**)&data2));
	free(data2);

	agile_chtbl_destroy(&htbl);
}
