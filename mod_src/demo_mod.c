//
//  Created by huanghaifeng on 15-11-25.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//

/*
void* __create__(void);
int __init__(void* instance, const char* parm);
void __release__(void* instance);
void __signal__(void* instance, int signal);
*/
#include "demo_mod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int gid = 0;

static void print_demo_t(demo_t* d)
{
	printf("printing...........%d\n", d->id);
	char* tmpbuf = malloc(10);
	sprintf(tmpbuf, "tmpbuf");
	sleep(5);
	printf("after sleep: %s\n", tmpbuf);
	free(tmpbuf);
	printf("print_demo_t[%d %s %s]\n", d->id, d->name, d->param);
}

void* __create__(void)
{
	printf("%s called\n", __FUNCTION__);
	demo_t* d = malloc(sizeof(*d));
	d->id = gid++;
	sprintf(d->name, "demo%d", d->id);
	memset(d->param, 0, sizeof(d->param));
	d->print = print_demo_t;
	return d;
}

int __init__(void* instance, const char* parm)
{
	printf("%s called\n", __FUNCTION__);
	demo_t* d = instance;
	sprintf(d->param, "%s", parm);
	return 0;
}

void __release__(void* instance)
{
	printf("%s(%s) called\n", __FUNCTION__, ((demo_t*)instance)->name);
	free(instance);
}

void __signal__(void* instance, int signal)
{
	printf("%s(%s %d) called\n", __FUNCTION__, ((demo_t*)instance)->name, signal);
}

