#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "cdplayer.h"

void check_int(int i, int target) {
	if (i == target) printf("==> success\n");
	else printf("==> failure\n");
}

void check_str(const char* s, const char* target) {
	if (strcmp(s, target) == 0) printf("==> success\n");
	else printf("==> failure\n");
}

int main() {
#if 0
	{
		initialize();

		onEvent(EV_PLAY_PAUSE);
		check_int(1, cmdIdx);
		check_str(buf[0], "start");

		onEvent(EV_PLAY_PAUSE);
		check_int(2, cmdIdx);
		check_str(buf[1], "pause");

		onEvent(EV_PLAY_PAUSE);
		check_int(3, cmdIdx);
		check_str(buf[2], "resume");
	}

	{
		initialize();

		onEvent(EV_PLAY_PAUSE);
		check_int(1, cmdIdx);
		check_str(buf[0], "start");

		onEvent(EV_STOP);
		check_int(2, cmdIdx);
		check_str(buf[1], "stop");
	}

	{
		initialize();

		onEvent(EV_PLAY_PAUSE);
		check_int(1, cmdIdx);
		check_str(buf[0], "start");

		onEvent(EV_PLAY_PAUSE);
		check_int(2, cmdIdx);
		check_str(buf[1], "pause");

		onEvent(EV_STOP);
		check_int(3, cmdIdx);
		check_str(buf[2], "stop");
	}
#else
	{
		initialize();

		onPlayOrPause();
		check_int(1, cmdIdx);
		check_str(buf[0], "start");

		onPlayOrPause();
		check_int(2, cmdIdx);
		check_str(buf[1], "pause");

		onPlayOrPause();
		check_int(3, cmdIdx);
		check_str(buf[2], "resume");
	}

	{
		initialize();

		onPlayOrPause();
		check_int(1, cmdIdx);
		check_str(buf[0], "start");

		onStop();
		check_int(2, cmdIdx);
		check_str(buf[1], "stop");
	}

	{
		initialize();

		onPlayOrPause();
		check_int(1, cmdIdx);
		check_str(buf[0], "start");

		onPlayOrPause();
		check_int(2, cmdIdx);
		check_str(buf[1], "pause");

		onStop();
		check_int(3, cmdIdx);
		check_str(buf[2], "stop");
	}
#endif

	getchar();
	return 0;
}
