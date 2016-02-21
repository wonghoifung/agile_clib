#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
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

static int compare_int(const void* int1, const void* int2) {
	if (*(const int*)int1 > *(const int*)int2) return 1;
	else if (*(const int*)int1 < *(const int*)int2) return -1;
	else return 0;
}

static int partition(void* data, int esize, int i, int k, int(*compare)(const void*,const void*)) {
	char* a = data;
	void* pval;
	void* temp;
	int r[3];
	if ((pval=malloc(esize))==NULL) return -1;
	if ((temp=malloc(esize))==NULL) {
		free(pval);
		return -1;
	}
	r[0] = (rand()%(k-i+1))+i;
	r[1] = (rand()%(k-i+1))+i;
	r[2] = (rand()%(k-i+1))+i;
	issort(r, 3, sizeof(r[0]), compare_int);
	memcpy(pval, &a[r[1]*esize], esize);
	i-=1;
	k+=1;
	while (1) {
		do { k-=1; } while (compare(&a[k*esize],pval) > 0);
		do { i+=1; } while (compare(&a[i*esize],pval) < 0);
		if (i >= k) break;
		memcpy(temp, &a[i*esize], esize);
		memcpy(&a[i*esize], &a[k*esize], esize);
		memcpy(&a[k*esize], temp, esize);
	}
	free(pval);
	free(temp);
	return k;
}

int qksort(void* data, int size, int esize, int i, int k, int(*compare)(const void*,const void*)) {
	int j;
	while (i < k) {
		if ((j=partition(data, esize, i, k, compare)) < 0) return -1;
		if (qksort(data, size, esize, i, j, compare) < 0) return -1;
		i = j + 1;
	}
	return 0;
}

static void dump_int_data(void* data, int size) {
	int i=0;
	for (; i<size; ++i) {
		printf("%d ",((int*)data)[i]);
	}
	printf("\n");
}

static int merge(void* data, int esize, int i, int j, int k, int(*compare)(const void*,const void*)) {
	char* a = data;
	char* m;
	int ipos,jpos,mpos;
	ipos = i;
	jpos = j + 1;
	mpos = 0;
	if ((m=(char*)malloc(esize*((k-i)+1)))==NULL) return -1;
	while (ipos <= j || jpos <= k) {
		if (ipos > j) {
			while (jpos <= k) {
				memcpy(&m[mpos*esize], &a[jpos*esize], esize);
				jpos+=1;
				mpos+=1;
			}
			continue;
		} else if (jpos > k) {
			while (ipos <= j) {
				memcpy(&m[mpos*esize], &a[ipos*esize], esize);
				ipos+=1;
				mpos+=1;
			}
			continue;
		}
		if (compare(&a[ipos*esize], &a[jpos*esize]) < 0) {
			memcpy(&m[mpos*esize], &a[ipos*esize], esize);
			ipos+=1;
			mpos+=1;
		} else {
			memcpy(&m[mpos*esize], &a[jpos*esize], esize);
			jpos+=1;
			mpos+=1;
		}
	}
	memcpy(&a[i*esize], m, esize*((k-i)+1));
	free(m);
	return 0;
}

int mgsort(void* data, int size, int esize, int i, int k, int(*compare)(const void*,const void*)) {
	int j;
	if (i < k) {
		j = (int)((i+k-1)/2);
		if (mgsort(data, size, esize, i, j, compare) < 0) return -1;
		if (mgsort(data, size, esize, j+1, k, compare) < 0) return -1;
		if (merge(data, esize, i, j, k, compare) < 0) return -1;
	}
	return 0;
}

// k is the biggest element among data plus 1
int ctsort(int* data, int size, int k) {
	int* counts;
	int* temp;
	int i,j;
	if ((counts=(int*)malloc(k*sizeof(int)))==NULL) return -1;
	if ((temp=(int*)malloc(size*sizeof(int)))==NULL) return -1;
	for (i=0; i<k; ++i) counts[i] = 0;
	for (j=0; j<size; ++j) counts[data[j]] = counts[data[j]] + 1;
	for (i=1; i<k; ++i) counts[i] += counts[i-1];
	for (j=size-1; j>=0; --j) {
		temp[counts[data[j]]-1] = data[j];
		counts[data[j]] -= 1;
	}
	memcpy(data, temp, size * sizeof(int));
	free(counts);
	free(temp);
	return 0;
}

// k(base) is for ctsort
int rxsort(int* data, int size, int p, int k) {
	int* counts;
	int* temp;
	int index, pval, i, j, n;
	if ((counts=(int*)malloc(k * sizeof(int))) == NULL) return -1;
	if ((temp=(int*)malloc(size * sizeof(int))) == NULL) return -1;
	for (n=0; n<p; ++n) {
		for (i=0; i<k; ++i) counts[i] = 0;
		pval = (int)pow((double)k, (double)n);
		for (j=0; j<size; ++j) {
			index = (int)(data[j]/pval) % k;
			counts[index] += 1;
		}
		for (i=1; i<k; ++i) counts[i] += counts[i-1];
		for (j=size-1; j>=0; --j) {
			index = (int)(data[j]/pval) % k;
			temp[counts[index]-1] = data[j];
			counts[index] -= 1;
		}
		memcpy(data, temp, size*sizeof(int));
	}
	free(counts);
	free(temp);
	return 0;
}

int bisearch(void* sorted, const void* target, int size, int esize, int(*compare)(const void*,const void*)) {
	int left, middle, right;
	left = 0;
	right = size - 1;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (compare(((char*)sorted + (esize * middle)), target)) {
			case -1: left = middle + 1; break;
			case 1: right = middle - 1; break;
			case 0: return middle;
			// no default
		}
	}
	return -1;
}

//////////////////////////////

//#include "test_common.h"
#include <stdio.h>

void test_agile_sort() {
	int arr[] = {5,7,9,1,3,8,6,2,0};
	int size = sizeof(arr)/sizeof(arr[0]);
	int esize = sizeof(arr[0]);
	int res;
	dump_int_data(arr, size);
	//res = issort(arr,size,esize,compare_int);
	//res = qksort(arr, size, esize, 0, size-1, compare_int);
	//res = mgsort(arr, size, esize, 0, size-1, compare_int);
	//res = ctsort(arr, size, 10); 
	res = rxsort(arr, size, 1, 10); 
	printf("res: %d\n", res);
	dump_int_data(arr, size);

	int target = 5;
	res = bisearch(arr, &target, size, esize, compare_int);
	if (res != -1) printf("found 5 at %d\n", res);
}
