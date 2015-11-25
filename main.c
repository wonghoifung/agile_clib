#include "agile_mem.h"
#include "agile_module.h"
#include "agile_signal.h"
#include <stdio.h>
#include <unistd.h>

agile_module* m = NULL;
void universal_signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		agile_dispose_module(&m);
		m = agile_load_module("./mod/demo_mod.so");
	}
}

int main()
{
	agile_signal_init();

	m = agile_load_module("./mod/demo_mod.so");

	while (1)
	{
		m->create();
		m->init(NULL, NULL);
		m->signal(NULL, 1);
		m->release(NULL);
		sleep(1);
	}
	
	agile_dispose_module(&m);

#ifdef _WIN32
	system("pause");
#endif

    return 0;
}


