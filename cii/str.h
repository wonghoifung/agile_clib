#ifndef STR_HEADER
#define STR_HEADER

#include <stdarg.h>

// 1 2  3  4  5  6
//  i  n  t  e  r
//-5 -4 -3 -2 -1 0

// exported functions
extern char* Str_sub(const char* s, int i, int j);
extern char* Str_dup(const char* s, int i, int j, int n);
extern char* Str_cat(const char* s1, int i1, int j1, const char* s2, int i2, int j2);
extern char* Str_catv(const char* s, ...); // s1 i1 j1 .... sn in jn NULL
extern char* Str_reverse(const char* s, int i, int j);
extern char* Str_map(const char* s, int i, int j, const char* from, const char* to);
extern int Str_pos(const char* s, int i);
extern int Str_len(const char* s, int i, int j);
extern int Str_cmp(const char* s1, int i1, int j1, const char* s2, int i2, int j2);
extern int Str_chr(const char* s, int i, int j, int c);
extern int Str_rchr(const char* s, int i, int j, int c);
extern int Str_upto(const char* s, int i, int j, const char* set);
extern int Str_rupto(const char* s, int i, int j, const char* set);
extern int Str_find(const char* s, int i, int j, const char* str);
extern int Str_rfind(const char* s, int i, int j, const char* str);

#undef T

#endif
