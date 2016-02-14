#ifndef agile_dlist_header
#define agile_dlist_header

#include <stdlib.h>

typedef struct agile_dlist_element_ {
	void* data;
	struct agile_dlist_element_* prev;
	struct agile_dlist_element_* next;
} agile_dlist_element;

typedef struct agile_dlist_ {
	int size;
	void (*destroy)(void* data);
	agile_dlist_element* head;
	agile_dlist_element* tail;
} agile_dlist;

void agile_dlist_init(agile_dlist* list, void(*destroy)(void*));
void agile_dlist_destroy(agile_dlist* list);
int agile_dlist_ins_next(agile_dlist* list, agile_dlist_element* element, const void* data);
int agile_dlist_ins_prev(agile_dlist* list, agile_dlist_element* element, const void* data);
int agile_dlist_remove(agile_dlist* list, agile_dlist_element* element, void** data);

#define agile_dlist_size(list) ((list)->size)
#define agile_dlist_head(list) ((list)->head)
#define agile_dlist_tail(list) ((list)->tail)
#define agile_dlist_is_head(element) ((element)->prev==NULL?1:0)
#define agile_dlist_is_tail(element) ((element)->next==NULL?1:0)
#define agile_dlist_data(element) ((element)->data)
#define agile_dlist_next(element) ((element)->next)
#define agile_dlist_prev(element) ((element)->prev)

void test_agile_dlist();

#endif
