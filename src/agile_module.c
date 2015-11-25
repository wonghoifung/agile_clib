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

static void open_module(agile_module** pm)
{
	agile_module* m = *pm;
	m->handle = dlopen(m->pathname, RTLD_NOW | RTLD_GLOBAL);
	if (!m->handle)
	{
		fprintf(stderr, "dlopen %s failed\n", m->pathname);
		free(m->pathname);
		free(m);
		*pm = NULL;
		return;
	}
	m->objcnt = 0;
	m->reloading = 0;
	m->create = dlsym(m->handle, "__create__");
	m->init = dlsym(m->handle, "__init__");
	m->release = dlsym(m->handle, "__release__");
	m->signal = dlsym(m->handle, "__signal__");
	assert(m->create);
	assert(m->init);
	assert(m->release);
	assert(m->signal);
}

agile_module* agile_load_module(const char* pathname)
{
	agile_module* m = malloc(sizeof(*m));
	if (!m)
	{
		fprintf(stderr, "malloc failed(%s)\n", pathname);
		return NULL;
	}
	m->pathname = agile_strclone(pathname);
	open_module(&m);
	return m;
}

static void reload_module(agile_module** pm)
{
	agile_module* m = *pm;
	dlclose(m->handle);
	open_module(pm);
	if (*pm)
	{
		printf("successfully reload module %s\n", m->pathname);
	}
}

void agile_reload_module(agile_module** pm)
{
	agile_module* m = *pm;
	if (m->objcnt == 0)
	{
		reload_module(&m);
		m->reloading = 0;
	}
	else
	{
		m->reloading = 1;
	}
}

void agile_dispose_module(agile_module** m)
{
	dlclose((*m)->handle);
	free((*m)->pathname);
	free(*m);
	*m = NULL;
}

void* create_mod_object(agile_module* m)
{
	if (m->reloading)
	{
		return NULL;
	}
	void* obj = m->create();
	m->objcnt += 1;
	return obj;
}

void destroy_mod_object(agile_module* m, void* obj)
{
	m->release(obj);
	m->objcnt -= 1;
	if (m->reloading && m->objcnt == 0)
	{
		reload_module(&m);
		m->reloading = 0;
	}
}

