#include <string.h>
#include "agile_dlist.h"

void agile_dlist_init(agile_dlist* list, void(*destroy)(void*)) {
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void agile_dlist_destroy(agile_dlist* list) {
	void* data;
	while (agile_dlist_size(list) > 0) {
		if (agile_dlist_remove(list, agile_dlist_tail(list), (void**)&data)==0 && list->destroy!=NULL) {
			list->destroy(data);
		}
	}
	memset(list, 0, sizeof(agile_dlist));
}

int agile_dlist_ins_next(agile_dlist* list, agile_dlist_element* element, const void* data) {
	agile_dlist_element* new_element;
	if (element==NULL && agile_dlist_size(list)!=0) { // TODO
		return -1;
	}
	if ((new_element=(agile_dlist_element*)malloc(sizeof(agile_dlist_element)))==NULL) {
		return -1; 
	}
	new_element->data = (void*)data;
	if (agile_dlist_size(list)==0) {
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	} else {
		new_element->next = element->next;
		new_element->prev = element;
		if (element->next==NULL) {
			list->tail = new_element;
		} else {
			element->next->prev = new_element;
		}
		element->next = new_element;
	}
	list->size += 1;
	return 0;
}

int agile_dlist_ins_prev(agile_dlist* list, agile_dlist_element* element, const void* data) {
	agile_dlist_element* new_element;
	if (element==NULL && agile_dlist_size(list)!=0) { // TODO
		return -1;
	}
	if ((new_element=(agile_dlist_element*)malloc(sizeof(agile_dlist_element)))==NULL) {
		return -1; 
	}
	new_element->data = (void*)data;
	if (agile_dlist_size(list)==0) {
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	} else {
		new_element->next = element;
		new_element->prev = element->prev;
		if (element->prev==NULL) {
			list->head = new_element;
		} else {
			element->prev->next = new_element;
		}
		element->prev = new_element;
	}
	list->size += 1;
	return 0;
}

int agile_dlist_remove(agile_dlist* list, agile_dlist_element* element, void** data) {
	if (element==NULL || agile_dlist_size(list)==0) return -1;
	*data = element->data;
	if (element==list->head) {
		list->head = element->next;
		if (list->head==NULL) {
			list->tail = NULL;
		} else {
			element->next->prev = NULL;
		}
	} else {
		element->prev->next = element->next;
		if (element->next == NULL) {
			list->tail = element->prev;
		} else {
			element->next->prev = element->prev;
		}
	}
	free(element);
	list->size -= 1;
	return 0;
}

//////////////////////////////

#include "test_common.h"

static void print_dlist(agile_dlist* list) {
	agile_dlist_element* elm = agile_dlist_head(list);
	printf("dlist: ");
	while (elm != NULL) {
		printf("%s ", (char*)agile_dlist_data(elm));
		elm = agile_dlist_next(elm);
	}
	printf("\n");
}

void test_agile_dlist() {
	agile_dlist list;
	agile_dlist_init(&list,free);
	
	char* data1 = get_data(1);
	agile_dlist_ins_next(&list,NULL,data1);

	char* data2 = get_data(2);
	agile_dlist_ins_next(&list,list.head,data2);

	char* data3 = get_data(3);
	agile_dlist_ins_prev(&list,list.tail,data3);

	print_dlist(&list);

	void* remdata;
	agile_dlist_remove(&list,list.tail,&remdata);
	printf("remove: %s\n",(char*)remdata);
	free(remdata);

	print_dlist(&list);

	agile_dlist_destroy(&list);
}
