#include <SDL2/SDL.h>
#include "header.h"

//According to the value of the pressed key a function is choosed.
static void	initialize_fun_key_triggered(char (*fun_update[])(t_scene *))
{
	fun_update[0] = &nothing;
	fun_update[1] = &quit;
	fun_update[2] = ortho_project;
}

//According to the value of the event (press key or not) a function is choosed.
static void	initialize_fun_event(int (*fun_event[])(int))
{
	fun_event[0] = &set_nothing;
	fun_event[1] = &set_quit;
	fun_event[2] = &set_index;
}

void initialize_fun(t_f *fun)
{
	initialize_fun_key_triggered((*fun).fun_update);
	initialize_fun_event((*fun).fun_event);
}
