//
//  Created by huanghaifeng on 15-11-25.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef DEMO_MOD_HEADER
#define DEMO_MOD_HEADER

struct demo_t;
typedef void(*print_func)(struct demo_t*);

typedef struct demo_t
{
	int id;
	char name[1024];
	char param[1024];
	print_func print;
} demo_t;


#endif
