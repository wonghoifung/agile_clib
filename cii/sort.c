#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"
#include "fmt.h"
#include "thread.h"
#include "mem.h"

// sort types

// sort data

// sort functions
int partition(int a[], int i, int j) {
	int v, k, t;
	j++;
	k = i;
	v = a[k];
	while (i < j) {
		i++; while (a[i] < v && i < j) i++;
		j--; while (a[j] > v) j--;
		if (i < j) {
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	t = a[k];
	a[k] = a[j];
	a[j] = t;
	return j;
}

int main(int argc, char* argv[]) {
	int i, n = 100000, *x, preempt;
	preempt = Thread_init(1, NULL);
	assert(preempt == 1);
	if (argc >= 2) n = atoi(argv[1]);
	x = CALLOC(n, sizeof (int));
	srand(time(NULL));
	for (i = 0; i < n; i++) x[i] = rand();
	sort(x, n, argc, argv);
	for (i = 1; i < n; i++)
		if (x[i] < x[i-1]) break;
	assert(i == n);
	Thread_exit(EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
