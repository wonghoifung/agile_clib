
//types

// macros
#define pad(n,c) do { \
	int nn = (n); \
	while (nn-- > 0) \
		put((c), cl); \
} while(0)

// conversion functons
static void cvt_s(int code, va_list* app, int put(int c, void* cl), void* cl, unsigned char flags[], int width, int precision) {
	char* str = va_arg(*app, char*);
	assert(str);
	Fmt_puts(str, strlen(str), put, cl, flags, width, precision);
}

// data

// static functions

// functons
void Fmt_puts(const char* str, int len, int put(int c, void* cl), void* cl, unsigned char flags[], int width, int precision) {
	assert(str);
	assert(len >= 0);
	assert(flags);

	// normalize width and flags
	// normalize width
	if (width == INT_MIN)
		width = 0;
	if (width < 0) {
		flags['-'] = 1;
		width = -width;
	}
	// normalize flags
	if (precision >= 0)
		flags['0'] = 0;

	if (precision >= 0 && precision < len)
		len = precision;

	if (!flags['-'])
		pad(width - len, ' ');

	// emit str[0..len-1]
	{
		int i;
		for (i = 0; i < len; i++)
			put((unsigned char)*str++, cl);
	}

	if (flags['-'])
		pad(width - len, ' ');
}