//
//  Created by huanghaifeng on 15-11-24.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef AGILE_MODULE_HEADER
#define AGILE_MODULE_HEADER

typedef void* (*dl_create)(void);
typedef int (*dl_init)(void* instance, const char* parm);
typedef void (*dl_release)(void* instance);
typedef void (*dl_signal)(void* instance, int signal);

typedef struct
{
	char* pathname;
	void* handle;
	dl_create create;
	dl_init init;
	dl_release release;
	dl_signal signal;
} agile_module;

agile_module* agile_load_module(const char* pathname);
void agile_dispose_module(agile_module** m);

#endif

