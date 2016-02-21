#include <stdlib.h>
#include <string.h>
#include "agile_sort.h"

int issort(void* data, int size, int esize, int(*compare)(const void*,const void*)) {
	char* a = data;
	void* key;
	int i,j;
	if ((key = (char*)malloc(esize))==NULL) return -1;
	for (j=1; j<size; ++j) {
		memcpy(key, &a[j*esize], esize);
		i=j-1;
		while (i >= 0 && compare(&a[i*esize],key) > 0) {
			memcpy(&a[(i+1)*esize], &a[i*esize], esize);
			i -= 1;
		}
		memcpy(&a[(i+1)*esize], key, esize);
	}
	free(key);
	return 0;
}

//////////////////////////////

//#include "test_common.h"
#include <stdio.h>

static int less(const void* e, const void* key) {
	int ie = *(int*)e;
	int k = *(int*)key;
	return k < ie;
}

void test_agile_sort() {
	int arr[] = {5,7,9,1,3,8,6,2,0,4};
	int size = sizeof(arr)/sizeof(arr[0]);
	int esize = sizeof(arr[0]);
	issort(arr,size,esize,less);
	int i=0;
	for (; i<size; ++i) {
		printf("%d ",arr[i]);
	}
	printf("\n");
}
