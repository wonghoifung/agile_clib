#include <string.h>
#include <limits.h>
#include "assert.h"
#include "fmt.h"
#include "str.h"
#include "mem.h"

// macros
#define idx(i,len) ((i) <= 0 ? (i) + (len) : (i) - 1)

#define convert(s, i, j) do { \
	int len; \
	assert(s); \
	len = strlen(s); \
	i = idx(i,len); \
	j = idx(j,len); \
	if (i > j) { \
		int t = i; \
		i = j; \
		j = t; \
	} \
	assert(i >= 0 && j <= len); \
} while (0)

// functions
char* Str_sub(const char* s, int i, int j) {
	char *str, *p;
	convert(s, i, j);
	p = str = ALLOC(j - i + 1);
	while (i < j) *p++ = s[i++];
	*p = '\0';
	return str;
}

char* Str_dup(const char* s, int i, int j, int n) {
	int k;
	char *str, *p;
	assert(n >= 0);
	convert(s, i, j);
	p = str = ALLOC(n * (j - i) + 1);
	if (j - i > 0)
		while (n-- > 0)
			for (k = i; k < j; k++)
				*p++ = s[k];
	*p = '\0';
	return str;
}

char* Str_reverse(const char* s, int i, int j) {
	char *str, *p;
	convert(s, i, j);
	p = str = ALLOC(j - i + 1);
	while (j > i) *p++ = s[--j];
	*p = '\0';
	return str;
}

char* Str_cat(const char* s1, int i1, int j1, const char* s2, int i2, int j2) {
	char *str, *p;
	convert(s1, i1, j1);
	convert(s2, i2, j2);
	p = str = ALLOC(j1 - i1 + j2 - i2 + 1);
	while (i1 < j1) *p++ = s1[i1++];
	while (i2 < j2) *p++ = s2[i2++];
	*p = '\0';
	return str;
}

char* Str_catv(const char* s, ...) {
	char *str, *p;
	const char* save = s;
	int i, j, len = 0;
	va_list ap;

	va_start(ap, s);

	// len <- the length of the result
	while (s) {
		i = va_arg(ap, int);
		j = va_arg(ap, int);
		convert(s, i, j);
		len += (j - i);
		s = va_arg(ap, const char*);
	}

	va_end(ap);

	p = str = ALLOC(len + 1);
	s = save;

	va_start(ap, s);

	// copy each s[i:j] to p, increment p
	while (s) {
		i = va_arg(ap, int);
		j = va_arg(ap, int);
		convert(s, i, j);
		while (i < j) *p++ = s[i++];
		s = va_arg(ap, const char*);
	}

	va_end(ap);

	*p = '\0';
	return str;
}

char* Str_map(const char* s, int i, int j, const char* from, const char* to) {
	static char map[256] = { 0 };
	if (from && to) {
		// rebuild map
		unsigned c;
		for (c = 0; c < sizeof map; c++)
			map[c] = c;
		while (*from && *to)
			map[(unsigned char)*from++] = *to++;
		assert(*from == 0 && *to == 0);
	} else {
		assert(from == NULL && to == NULL && s);
		assert(map['a']);
	}

	if (s) {
		// map s[i:j] into a new string
		char *str, *p;
		convert(s, i, j);
		p = str = ALLOC(j - i + 1);
		while (i < j) *p++ = map[(unsigned char)s[i++]];
		*p = '\0';

		return str;
	} else {
		return NULL;
	}
}

int Str_pos(const char* s, int i) {
	int len;
	assert(s);
	len = strlen(s);
	i = idx(i,len);
	assert(i >= 0 && i <= len);
	return i + 1;
}

int Str_len(const char* s, int i, int j) {
	convert(s, i, j);
	return j - i;
}

int Str_cmp(const char* s1, int i1, int j1, const char* s2, int i2, int j2) {
	// string compare
	convert(s1, i1, j1);
	convert(s2, i2, j2);
	s1 += i1;
	s2 += i2;
	if (j1 - i1 < j2 - i2) {
		int cond = strncmp(s1, s2, j1 - i1);
		return cond == 0 ? -1 : cond;
	} else if (j1 - i1 > j2 - i2) {
		int cond = strncmp(s1, s2, j2 - i2);
		return cond == 0 ? +1 : cond;
	} else {
		return strncmp(s1, s2, j1 - i1);
	}
}
