#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "array_list.h"

ArrayList* add_to_array_list(ArrayList* pThis, void* pData) {
	assert(pThis->capacity > pThis->index);
	pThis->pBuf[pThis->index++] = pData;
	return pThis;
}

void* remove_from_array_list(ArrayList* pThis, void* pData) {
	int i;
	for (i = 0; i < pThis->index; ++i) {
		if (pThis->pBuf[i] == pData) {
			memmove(pThis->pBuf + i, pThis->pBuf + i + 1, (pThis->index - i - 1) * sizeof(void*));
			--pThis->index;
			return pData;
		}
	}
	return NULL;
}

void* get_from_array_list(ArrayList* pThis, int index) {
	assert(0 <= index && pThis->index > index);
	return pThis->pBuf[index];
}

size_t array_list_size(ArrayList* pThis) {
	return pThis->index;
}
