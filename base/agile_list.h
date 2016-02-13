#ifndef agile_list_header
#define agile_list_header

#include <stdlib.h>

typedef struct agile_list_element_ {
	void* data;
	struct agile_list_element_* next;
} agile_list_element;

typedef struct agile_list_ {
	int size;
	//int (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);
	agile_list_element* head;
	agile_list_element* tail;
} agile_list;

void agile_list_init(agile_list* list, void(*destroy)(void*));
void agile_list_destroy(agile_list* list);
int agile_list_ins_next(agile_list* list, agile_list_element* element, const void* data);
int agile_list_rem_next(agile_list* list, agile_list_element* element, void** data);

#define agile_list_size(list) ((list)->size)
#define agile_list_head(list) ((list)->head)
#define agile_list_tail(list) ((list)->tail)
#define agile_list_is_head(list,element) ((element)==(list)->head?1:0)
#define agile_list_is_tail(element) ((element)->next==NULL?1:0)
#define agile_list_data(element) ((element)->data)
#define agile_list_next(element) ((element)->next)

#endif
