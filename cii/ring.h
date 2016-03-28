#ifndef RING_HEADER
#define RING_HEADER

#define T Ring_T

typedef struct T* T;

// exported functions
extern T Ring_new(void);
extern T Ring_ring(void* x, ...);

#undef T

#endif
