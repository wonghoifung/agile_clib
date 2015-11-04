#include "agile_mem.h"
#include <stdio.h>

int main()
{
    char* s = (char*)agile_aligned_malloc(128, 32);
    agile_aligned_free(s);

    int** arr = agile_alloc2d_int(10,20);
    free(arr);
    
    return 0;
}


