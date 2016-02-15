#ifndef agile_queue_header
#define agile_queue_header

#include <stdlib.h>
#include "agile_list.h"

typedef agile_list agile_queue;

#define agile_queue_init agile_list_init
#define agile_queue_destroy agile_list_destroy

int agile_queue_enqueue(agile_queue* queue, const void* data);
int agile_queue_dequeue(agile_queue* queue, void** data);

#define agile_queue_peek(queue) ((queue)->head==NULL?NULL:(queue)->head->data)
#define agile_queue_size agile_list_size

void test_agile_queue();

#endif
