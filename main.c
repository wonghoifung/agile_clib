#include "agile_mem.h"
#include "agile_module.h"
#include "agile_signal.h"
#include "mod_src/demo_mod.h"
#include "globals.h"

agile_module* m = NULL;

void exit_handler()
{
	if (m)
	{
		printf("dispose\n");
		agile_dispose_module(&m);
	}
}

void universal_signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		agile_reload_module(&m);
		return;
	}
	exit(0);
}

int main()
{
	atexit(exit_handler);

#ifndef VALGRIND
	printf("set_rlimit\n");
	set_rlimit();
#endif

	agile_signal_init();

	m = agile_load_module("./mod/demo_mod.so");

	while (1)
	{
		demo_t* d = create_mod_object(m);
		if (d == NULL)
		{
			printf("d is null\n");
			sleep(1);
			continue;
		}
		m->init(d, "helloworld");
		m->signal(d, 1);
		d->print(d);
		destroy_mod_object(m, d);
	}

	agile_dispose_module(&m);

    return 0;
}


