//
//  Created by huanghaifeng on 15-11-25.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef GLOBALS_HEADER
#define GLOBALS_HEADER

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

inline void set_rlimit()
{
	struct rlimit rlim, rlim_new;

	if (getrlimit(RLIMIT_NOFILE, &rlim) == 0)
	{
		rlim_new.rlim_cur = rlim_new.rlim_max = 100000;
		if (setrlimit(RLIMIT_NOFILE, &rlim_new) != 0)
		{
			fprintf(stderr, "set rlimit file failure\n");
			exit(0);
		}
	}

	if (getrlimit(RLIMIT_CORE, &rlim) == 0)
	{
		rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;
		if (setrlimit(RLIMIT_CORE, &rlim_new) != 0)
		{
			fprintf(stderr, "set rlimit core failure\n");
			exit(0);
		}
	}
}

#endif
