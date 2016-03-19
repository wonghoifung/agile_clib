#ifndef ATOM_HEADER
#define ATOM_HEADER

extern int Atom_length(const char* str);
extern const char* Atom_new(const char* str, int len);
extern const char* Atom_string(const char* str);
extern const char* Atom_int(long n);

#endif
