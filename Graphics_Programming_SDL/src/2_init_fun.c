#include "header.h"

//Fill triangle
static void	initialize_draw_ft(void (*draw_ft[])(t_pixel_info *t_pixel_info, int i))
{
	draw_ft[0] = &draw_ft012;
	draw_ft[1] = &draw_ft021;
	draw_ft[2] = &draw_ft102;
	draw_ft[4] = &draw_ft120;
	draw_ft[8] = &draw_ft201;
	draw_ft[16] = &draw_ft210;
}

//Back face culling or not
static void	initialize_culling(void (*culling[])(t_scene *scene, int i, t_pixel_info *pixel_info))
{
	culling[0] = &triangle_to_nowhere;
	culling[1] = &triangle_to_color_buffer;
}

//DDA functions
static void	initialize_dda(void	(*dda[])(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda))
{
	dda[0] = &dda_y_minus;
	dda[1] = &dda_y_plus;
	dda[2] = &dda_x_minus;
	dda[4] = &dda_x_plus;
	dda[8] = &y_minus;	
	dda[16] = &y_plus;
	dda[32] = &x_minus;
	dda[64] = &x_plus;
}

//Delay or not
static void	initialize_delay(void (*fun_event[])(int))
{
	fun_event[0] = &do_not_delay;
	fun_event[1] = &delay;
}

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
	fun_update[2] = perspective_project;
	fun_update[4] = perspective_project_zoom_minus;
	fun_update[8] = perspective_project_zoom_plus;
	fun_update[16] = perspective_project_far;
	fun_update[32] = perspective_project_close;
	fun_update[64] = rotation_x_minus;
	fun_update[128] = rotation_x_plus;
	fun_update[256] = rotation_y_minus;
	fun_update[512] = rotation_y_plus;	
	fun_update[1024] = rotation_z_minus;
	fun_update[2048] = rotation_z_plus;
}

//According to the value of the event (press key or not) a function is choosed.
static void	initialize_fun_event(int (*fun_event[])(t_keys *))
{
	fun_event[0] = &set_nothing;
	fun_event[1] = &set_quit;
	fun_event[2] = &set_index;
}

void	initialize_fun(t_f *fun)
{
	initialize_fun_key_triggered((*fun).fun_update);
	initialize_fun_event((*fun).fun_event);
	initialize_fun_draw_pixel((*fun).fun_draw_pixel);
	initialize_delay((*fun).fun_delay);
	initialize_dda((*fun).dda);
	initialize_culling((*fun).culling);
	initialize_draw_ft((*fun).draw_ft);
}
