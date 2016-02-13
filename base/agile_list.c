#include <stdlib.h>
#include <string.h>
#include "agile_list.h"

void agile_list_init(agile_list* list, void(*destroy)(void*)) {
	list->size = 0;
	//list->match = NULL;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void agile_list_destroy(agile_list* list) {
	void* data;
	while (agile_list_size(list) > 0) {
		if (agile_list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL) {
			list->destroy(data);
		}
	}
	memset(list, 0, sizeof(agile_list));
}

// 1. insert data next to element if element is not null
// 2. insert data to list head if element is null
int agile_list_ins_next(agile_list* list, agile_list_element* element, const void* data) {
	agile_list_element* new_element;
	if ((new_element=(agile_list_element*)malloc(sizeof(agile_list_element)))==NULL) {
		return -1;
	}
	new_element->data = (void*)data;
	if (element==NULL) {
		if (agile_list_size(list)==0) {
			list->tail = new_element;
		}
		new_element->next = list->head;
		list->head = new_element;
	} else {
		if (element->next==NULL) {
			list->tail = new_element;
		}
		new_element->next = element->next;
		element->next = new_element;
	}
	list->size += 1;
	return 0;
}

// 1. delete data next to element if element is not null
// 2. delete head data if element is null
int agile_list_rem_next(agile_list* list, agile_list_element* element, void** data) {
	agile_list_element* old_element;
	if (agile_list_size(list)==0) {
		return -1;
	}
	if (element==NULL) {
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;
		if (agile_list_size(list)==1) {
			list->tail = NULL;
		}
	} else {
		if (element->next == NULL) {
			return -1;
		}
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;
		if (element->next == NULL) {
			list->tail = element;
		}
	}
	free(old_element);
	list->size -= 1;
	return 0;
}

