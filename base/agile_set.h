#ifndef agile_set_header
#define agile_set_header

#include <stdlib.h>
#include "agile_list.h"

typedef agile_list agile_set;

void agile_set_init(agile_set* set, int(*match)(const void*, const void*), void(*destroy)(void*));

#define agile_set_destroy agile_list_destroy

int agile_set_insert(agile_set* set, const void* data);
int agile_set_remove(agile_set* set, void** data);
int agile_set_union(agile_set* setu, const agile_set* set1, const agile_set* set2);
int agile_set_intersection(agile_set* seti, const agile_set* set1, const agile_set* set2);
int agile_set_difference(agile_set* setd, const agile_set* set1, const agile_set* set2);
int agile_set_is_member(const agile_set* set, const void* data);
int agile_set_is_subset(const agile_set* set1, const agile_set* set2);
int agile_set_is_equal(const agile_set* set1, const agile_set* set2);

#define agile_set_size(set) ((set)->size)

void test_agile_set();

#endif
