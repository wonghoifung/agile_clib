#ifndef agile_clist_header
#define agile_clist_header

#include <stdlib.h>

typedef struct agile_clist_element_ {
	void* data;
	struct agile_clist_element_* next;
} agile_clist_element;

typedef struct agile_clist_ {
	int size;
	void (*destroy)(void* data);
	agile_clist_element* head;
} agile_clist;

void agile_clist_init(agile_clist* list, void(*destroy)(void*));
void agile_clist_destroy(agile_clist* list);
int agile_clist_ins_next(agile_clist* list, agile_clist_element* element, const void* data);
int agile_clist_rem_next(agile_clist* list, agile_clist_element* element, void** data);

#define agile_clist_size(list) ((list)->size)
#define agile_clist_head(list) ((list)->head)
#define agile_clist_data(element) ((element)->data)
#define agile_clist_next(element) ((element)->next)

void test_agile_clist();

#endif
