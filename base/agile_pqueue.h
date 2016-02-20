#ifndef agile_pqueue_header
#define agile_pqueue_header

#include "agile_heap.h"

typedef agile_heap agile_pqueue;

#define agile_pqueue_init agile_heap_init
#define agile_pqueue_destroy agile_heap_destroy
#define agile_pqueue_insert agile_heap_insert
#define agile_pqueue_extract agile_heap_extract
#define agile_pqueue_peek(pqueue) ((pqueue)->tree==NULL?NULL:(pqueue)->tree[0])
#define agile_pqueue_size agile_heap_size

void test_agile_pqueue();

#endif
