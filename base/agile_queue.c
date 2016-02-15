#include "agile_queue.h"

int agile_queue_enqueue(agile_queue* queue, const void* data) {
	return agile_list_ins_next(queue, agile_list_tail(queue), data);
}

int agile_queue_dequeue(agile_queue* queue, void** data) {
	return agile_list_rem_next(queue, NULL, data);
}

//////////////////////////////

#include "test_common.h"

void test_agile_queue() {
	agile_queue queue;
	agile_queue_init(&queue, free);
	
	char* data1 = get_data(1);
	agile_queue_enqueue(&queue, data1);

	char* data2 = get_data(2);
	agile_queue_enqueue(&queue, data2);

	char* data3 = get_data(3);
	agile_queue_enqueue(&queue, data3);

	void* data;
	while (agile_queue_size(&queue) > 0) {
		agile_queue_dequeue(&queue, &data);
		printf("%s\n", (char*)data);
		free(data);
	}

	agile_queue_destroy(&queue);
}
