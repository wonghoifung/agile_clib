#ifndef XP_HEADER
#define XP_HEADER

#define T XP_T

typedef unsigned char* T;

// exported functions
extern int XP_add(int n, T z, T x, T y, int carry);
extern int XP_sub(int n, T z, T x, T y, int borrow);
extern int XP_mul(T z, int n, T x, int m, T y);

#undef T

#endif
