// reference: http://coolshell.cn/articles/10975.html

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

int function(void) {
	static int i, state = 0;
	switch (state) {
	case 0: goto LABEL0;
	case 1: goto LABEL1;
	}
LABEL0:
	for (i = 0; i < 10; ++i) {
		state = 1;
		return i;
	LABEL1:;
	}
	return -1;
}

int function2(void) {
	static int i, state = 0;
	switch (state) {
	case 0:
		for (i = 0; i < 10; ++i) {
			state = 1;
			return i;
	case 1:;
		}
	}
	return -1;
}

int function3(void) {
	static int i, state = 0;
	switch (state) {
	case 0:
		for (i = 0; i < 10; ++i) {
			state = __LINE__ + 2;
			return i;
	case __LINE__:;
		}
	}
	return -1;
}

#define Begin() static int state=0; switch(state) {case 0:
#define Yield(x) do {state=__LINE__; return x; case __LINE__:;} while (0)
#define End() }

int function4(void) {
	static int i;
	Begin();
	for (i=0; i<10; ++i) 
		Yield(i);
	End();
	return -1;
}

int main(int argc, char* argv[]) {
	for (size_t i = 0; i < 20; i++)
	{
		printf("%d\n", function4());
	}
}


