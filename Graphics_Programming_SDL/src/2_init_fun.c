#include <SDL2/SDL.h>
#include "header.h"

//According to the coordinate value the pixel is displayed or not.
static void	initialize_fun_draw_pixel(void (*fun_draw_pixel[])(t_pixel_info *))
{
	fun_draw_pixel[0] = &do_not_draw_pixel;
	fun_draw_pixel[1] = &draw_pixel;
}

//According to the value of the pressed key a function is choosed.
static void	initialize_fun_key_triggered(char (*fun_update[])(t_scene *))
{
	fun_update[0] = &nothing;
	fun_update[1] = &quit;
	fun_update[2] = ortho_project;
	fun_update[4] = ortho_project_zoom_minus;
	fun_update[8] = ortho_project_zoom_plus;
}

//According to the value of the event (press key or not) a function is choosed.
static void	initialize_fun_event(int (*fun_event[])(t_keys *))
{
	fun_event[0] = &set_nothing;
	fun_event[1] = &set_quit;
	fun_event[2] = &set_index;
	fun_event[4] = &set_index;
}

void initialize_fun(t_f *fun)
{
	initialize_fun_key_triggered((*fun).fun_update);
	initialize_fun_event((*fun).fun_event);
	initialize_fun_draw_pixel((*fun).fun_draw_pixel);
}
