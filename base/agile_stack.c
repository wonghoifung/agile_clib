#include "agile_stack.h"

int agile_stack_push(agile_stack* stack, const void* data) {
	return agile_list_ins_next(stack, NULL, data);
}

int agile_stack_pop(agile_stack* stack, void** data) {
	return agile_list_rem_next(stack, NULL, data);
}

//////////////////////////////

#include "test_common.h"

void test_agile_stack() {
	agile_stack stack;
	agile_stack_init(&stack, free);

	char* data1 = get_data(1);
	agile_stack_push(&stack, data1);

	char* data2 = get_data(2);
	agile_stack_push(&stack, data2);

	char* data3 = get_data(3);
	agile_stack_push(&stack, data3);

	void* data;
	while (agile_stack_size(&stack) > 0) {
		agile_stack_pop(&stack, &data);
		printf("%s\n",(char*)data);
		free(data);
	}

	agile_stack_destroy(&stack);
}
