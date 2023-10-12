#include <SDL2/SDL.h>
#include "header.h"

void	initialize_fun_key_triggered(char (*fun[])(int *))
{
	fun[0] = &nothing;
	fun[1] = &quit;
	fun[2] = &circle;
	fun[4] = &square;
}

void	initialize_fun_event(int (*fun_event[])(int))
{
	fun_event[0] = &set_nothing;
	fun_event[1] = &set_quit;
	fun_event[2] = &set_index;
}
