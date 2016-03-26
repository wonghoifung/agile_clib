#ifndef SET_HEADER
#define SET_HEADER

#define T Set_T

typedef struct T* T;

// exported functions
extern T Set_new(int hint, int cmp(const void* x, const void* y), unsigned hash(const void* x));
extern void Set_free(T* set);
extern int Set_length(T set);
extern int Set_member(T set, const void* member);
extern void Set_put(T set, const void* member);
extern void* Set_remove(T set, const void* member);

#undef T

#endif

