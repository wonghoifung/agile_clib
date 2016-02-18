#ifndef agile_heap_header
#define agile_heap_header

typedef struct agile_heap_ {
	int size;
	int (*compare)(const void* key1, const void* key2);
	void (*destroy)(void* data);
	void** tree;
} agile_heap;

void agile_heap_init(agile_heap* heap, int(*compare)(const void*,const void*), void(*destroy)(void*));
void agile_heap_destroy(agile_heap* heap);
int agile_heap_insert(agile_heap* heap, const void* data);
int agile_heap_extract(agile_heap* heap, void** data);

#define agile_heap_size(heap) ((heap)->size)

void test_agile_heap();

#endif

