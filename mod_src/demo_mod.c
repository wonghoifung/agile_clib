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

#include <stdio.h>

void* __create__(void)
{
	printf("%s called\n", __FUNCTION__);
}

int __init__(void* instance, const char* parm)
{
	printf("%s called\n", __FUNCTION__);
}

void __release__(void* instance)
{
	printf("%s called\n", __FUNCTION__);
}

void __signal__(void* instance, int signal)
{
	printf("%s called\n", __FUNCTION__);
}

