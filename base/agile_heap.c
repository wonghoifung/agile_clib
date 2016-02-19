#include <stdlib.h>
#include <string.h>
#include "agile_heap.h"

#define heap_parent(npos) ((int) ( ((npos)-1) / 2 ))
#define heap_left(npos) ( ((npos)*2) + 1 )
#define heap_right(npos) ( ((npos)*2) + 2 )

void agile_heap_init(agile_heap* heap, int(*compare)(const void*,const void*), void(*destroy)(void*)) {
	heap->size = 0;
	heap->compare = compare;
	heap->destroy = destroy;
	heap->tree = NULL;
}

void agile_heap_destroy(agile_heap* heap) {
	int i;
	if (heap->destroy != NULL) {
		for (i=0; i<agile_heap_size(heap); ++i) {
			heap->destroy(heap->tree[i]);
		}
	}
	free(heap->tree);
	memset(heap, 0, sizeof(agile_heap));
}

int agile_heap_insert(agile_heap* heap, const void* data) {
	void* temp;
	int ipos;
	int ppos;
	if ((temp=(void**)realloc(heap->tree, (agile_heap_size(heap)+1)*sizeof(void*)))==NULL) return -1;
	heap->tree = temp;
	heap->tree[agile_heap_size(heap)] = (void*)data;
	ipos = agile_heap_size(heap);
	ppos = heap_parent(ipos);
	while (ipos > 0 && heap->compare(heap->tree[ppos],heap->tree[ipos]) < 0) {
		temp = heap->tree[ppos];
		heap->tree[ppos] = heap->tree[ipos];
		heap->tree[ipos] = temp;

		ipos = ppos;
		ppos = heap_parent(ipos);
	}
	heap->size += 1;
	return 0;
}

int agile_heap_extract(agile_heap* heap, void** data) {

}

//////////////////////////////

#include "test_common.h"

void test_agile_heap() {

}
