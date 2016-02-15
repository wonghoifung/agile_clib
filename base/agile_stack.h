#ifndef agile_stack_header
#define agile_stack_header

#include <stdlib.h>
#include "agile_list.h"

typedef agile_list agile_stack;

#define agile_stack_init agile_list_init
#define agile_stack_destroy agile_list_destroy

int agile_stack_push(agile_stack* stack, const void* data);
int agile_stack_pop(agile_stack* stack, void** data);

#define agile_stack_peek(stack) ((stack)->head==NULL?NULL:(stack)->head->data)
#define agile_stack_size agile_list_size 

void test_agile_stack();

#endif
