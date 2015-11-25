//
//  Created by huanghaifeng on 15-11-25.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "agile_signal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef void (*signal_handler)(int signo);

void universal_signal_handler(int sig);

static int signals[] = { SIGQUIT, SIGTERM, SIGINT, SIGHUP, SIGUSR1, SIGUSR2, SIGCHLD, SIGSYS, SIGPIPE, 0 };

static signal_handler handlers[] = {
	universal_signal_handler,
	universal_signal_handler,
	universal_signal_handler,
	universal_signal_handler,
	universal_signal_handler,
	universal_signal_handler,
	universal_signal_handler,
	SIG_IGN,
	SIG_IGN,
	NULL
};

void agile_signal_init()
{
	size_t i = 0;
	struct sigaction sa;
	for (i = 0; signals[i] != 0; ++i)
	{
		memset(&sa, 0, sizeof(struct sigaction));
		sa.sa_handler = handlers[i];
		sigemptyset(&sa.sa_mask);
		if (sigaction(signals[i], &sa, NULL) == -1)
		{
			fprintf(stderr, "sigaction(%d) failed\n", signals[i]);
			exit(0);
		}
	}
}


