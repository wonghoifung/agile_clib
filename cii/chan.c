#include <string.h>
#include "assert.h"
#include "mem.h"
#include "chan.h"
#include "sem.h"

#define T Chan_T

struct T {
	const void* ptr;
	int* size;
	Sem_T send, recv, sync;
};

// chan functions

