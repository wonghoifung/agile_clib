#include <stdio.h>
#include "agile_list.h"

char* get_data(int i) {
	char* data1 = (char*)malloc(32);
	sprintf(data1, "helloworld%d", i);
	return data1;
}

void print_list(agile_list* list) {
	agile_list_element* elm = agile_list_head(list);
	printf("list: ");
	while (elm != NULL) {
		printf("%s ", agile_list_data(elm));
		elm = agile_list_next(elm);
	}
	printf("\n");
}

int main() {
	agile_list list;
	agile_list_init(&list, free);

	char* data1 = get_data(1);
	agile_list_ins_next(&list, NULL, data1);

	char* data2 = get_data(2);
	agile_list_ins_next(&list, NULL, data2);

	char* data3 = get_data(3);
	agile_list_ins_next(&list, NULL, data3);

	print_list(&list);

	void* resdata;
	agile_list_rem_next(&list, NULL, &resdata);
	printf("%s\n",(char*)resdata);
	free(resdata);

	print_list(&list);

	agile_list_destroy(&list);
	return 0;
}



