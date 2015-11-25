//
//  Created by huanghaifeng on 15-11-24.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "agile_module.h"
#include "agile_mem.h"
#include <assert.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

agile_module* agile_load_module(const char* pathname)
{
	agile_module* m = malloc(sizeof(*m));
	if (!m)
	{
		fprintf(stderr, "malloc failed(%s)\n", pathname);
		return NULL;
	}
	m->pathname = agile_strclone(pathname);
	m->handle = dlopen(m->pathname, RTLD_NOW | RTLD_GLOBAL);
	if (!m->handle)
	{
		fprintf(stderr, "dlopen %s failed\n", m->pathname);
		free(m->pathname);
		free(m);
		return NULL;
	}
	m->create = dlsym(m->handle, "__create__");
	m->init = dlsym(m->handle, "__init__");
	m->release = dlsym(m->handle, "__release__");
	m->signal = dlsym(m->handle, "__signal__");
	assert(m->create);
	assert(m->init);
	assert(m->release);
	assert(m->signal);
	return m;
}

void agile_dispose_module(agile_module** m)
{
	dlclose((*m)->handle);
	free((*m)->pathname);
	free(*m);
	*m = NULL;
}


