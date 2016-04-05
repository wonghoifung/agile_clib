#ifndef AP_HEADER
#define AP_HEADER

#include <stdarg.h>

#define T AP_T

typedef struct T* T;

// exported functions
extern T AP_new(long int n);
extern T AP_fromstr(const char* str, int base, char** end);

#undef T

#endif
