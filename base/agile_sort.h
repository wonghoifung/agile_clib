#ifndef agile_sort_header
#define agile_sort_header

int issort(void* data, int size, int esize, int(*compare)(const void*,const void*));
int qksort(void* data, int size, int esize, int i, int k, int(*compare)(const void*,const void*));
int mgsort(void* data, int size, int esize, int i, int k, int(*compare)(const void*,const void*));
int ctsort(int* data, int size, int k);
int rxsort(int* data, int size, int p, int k);
int bisearch(void* sorted, const void* target, int size, int esize, int(*compare)(const void*,const void*));

void test_agile_sort();

#endif
