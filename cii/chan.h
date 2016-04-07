#ifndef CHAN_HEADER
#define CHAN_HEADER

#define T Chan_T

typedef struct T* T;

extern T Chan_new(void);
extern int Chan_send(T c, const void* ptr, int size);
extern int Chan_receive(T c, void* ptr, int size);

#undef T

#endif

