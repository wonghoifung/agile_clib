#include <stdlib.h>
#include <string.h>
#include "agile_pqueue.h"

//////////////////////////////

#include "test_common.h"

void test_agile_pqueue() {
	agile_pqueue pqueue;
	agile_pqueue_init(&pqueue, string_compare, free);
	char* d1 = get_data(1);
	char* d2 = get_data(2);
	char* d3 = get_data(3);
	char* d4 = get_data(4);
	agile_pqueue_insert(&pqueue, (void*)d2);
	agile_pqueue_insert(&pqueue, (void*)d4);
	agile_pqueue_insert(&pqueue, (void*)d3);
	agile_pqueue_insert(&pqueue, (void*)d1);
	void* md = NULL;
	printf("peek: %s\n", (char*)agile_pqueue_peek(&pqueue));
	agile_pqueue_extract(&pqueue, &md);
	printf("%s\n", (char*)md);
	free(md); md = NULL;
	printf("peek: %s\n", (char*)agile_pqueue_peek(&pqueue));
	agile_pqueue_extract(&pqueue, &md);
	printf("%s\n", (char*)md);
	free(md); md = NULL;
	printf("peek: %s\n", (char*)agile_pqueue_peek(&pqueue));
	agile_pqueue_extract(&pqueue, &md);
	printf("%s\n", (char*)md);
	free(md); md = NULL;
	printf("peek: %s\n", (char*)agile_pqueue_peek(&pqueue));
	agile_pqueue_extract(&pqueue, &md);
	printf("%s\n", (char*)md);
	free(md); md = NULL;
	printf("%d\n", agile_pqueue_extract(&pqueue, &md));
	agile_pqueue_destroy(&pqueue);
}
