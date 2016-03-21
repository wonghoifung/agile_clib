#ifndef EXCEPT_HEADER
#define EXCEPT_HEADER

#include <setjmp.h>

#define T Except_T

typedef struct T {
	const char* reason;
} T;

// types
typedef struct Except_Frame Except_Frame;
struct Except_Frame {
	Except_Frame* prev;
	jmp_buf env;
	const char* file;
	int line;
	const T* exception;
};
enum {
	Except_entered = 0,
	Except_raised,
	Except_handled,
	Except_finalized,
};

// variables
extern Except_Frame* Except_stack;

// functions
void Except_raise(const T* e, const char* file, int line);

// macros
#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__)
#define RERAISE(e) Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line)

#define RETURN switch (/*pop*/,0) default: return

#define TRY do { \
	volatile int Except_flag; \
	Except_Frame Except_frame; \
	// push \
	Except_flag = setjmp(Except_frame.env); \
	if (Except_flag == Except_entered) {



#endif
