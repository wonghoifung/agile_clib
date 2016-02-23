#include <string.h>
#include "agile_clist.h"

void agile_clist_init(agile_clist* list, void(*destroy)(void*)) {
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
}

void agile_clist_destroy(agile_clist* list) {
	void* data;
	while (agile_clist_size(list) > 0) {
		if (agile_clist_rem_next(list, list->head, (void**)&data)==0 && list->destroy!=NULL) {
			list->destroy(data);
		}
	}
	memset(list, 0, sizeof(agile_clist));
}

int agile_clist_ins_next(agile_clist* list, agile_clist_element* element, const void* data) {
	agile_clist_element* new_element;
	if ((new_element=(agile_clist_element*)malloc(sizeof(agile_clist_element)))==NULL) {
		return -1;
	}
	new_element->data = (void*)data;
	if (agile_clist_size(list)==0) {
		new_element->next = new_element;
		list->head = new_element;
	} else {
		new_element->next = element->next;
		element->next = new_element;
	}
	list->size += 1;
	return 0;
}

int agile_clist_rem_next(agile_clist* list, agile_clist_element* element, void** data) {
	agile_clist_element* old_element;
	if (agile_clist_size(list)==0) return -1;
	*data = element->next->data;
	if (element->next==element) {
		old_element = element->next;
		list->head = NULL;
	} else {
		old_element = element->next;
		element->next = element->next->next;
		if (old_element==agile_clist_head(list)) {
			list->head = old_element->next;
		}
	}
	free(old_element);
	list->size -= 1;
	return 0;
}

//////////////////////////////

#include "test_common.h"

static void print_clist(agile_clist* list) {
	agile_clist_element* elm = agile_clist_head(list);
	printf("clist: ");
	do {
		printf("%s ", (char*)agile_clist_data(elm));
		elm = agile_clist_next(elm);
	} while (elm != agile_clist_head(list));
	printf("\n");
}

void test_agile_clist() {
	agile_clist list;
	agile_clist_init(&list,free);

	char* data1 = get_data(1);
	agile_clist_ins_next(&list, NULL, data1);

	char* data2 = get_data(2);
	agile_clist_ins_next(&list, agile_clist_head(&list), data2);

	char* data3 = get_data(3);
	agile_clist_ins_next(&list, agile_clist_head(&list), data3);

	char* data4 = get_data(4);
	agile_clist_ins_next(&list, agile_clist_head(&list), data4);

	// 1 4 3 2
	print_clist(&list);

	void* remdata;
	agile_clist_rem_next(&list, agile_clist_head(&list), &remdata);
	printf("remove %s\n",(char*)remdata);
	free(remdata);

	// 1 3 2
	print_clist(&list);

	char* data5 = get_data(5);
	agile_clist_element* element = list.head->next;
	agile_clist_ins_next(&list, element, data5);

	// 1 3 5 2
	print_clist(&list);

	element = element->next->next;
	agile_clist_rem_next(&list, element, &remdata);
	printf("remove %s\n",(char*)remdata);
	free(remdata);

	// 3 5 2
	print_clist(&list);

	agile_clist_destroy(&list);
}
