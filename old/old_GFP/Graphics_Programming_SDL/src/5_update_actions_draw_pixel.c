#include "header.h"

void	draw_pixel(t_pixel_info *pixel_info)
{
	*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) = (*pixel_info).depth;
	*((*(*pixel_info).scene).color_buffer + (*pixel_info).cell) = (*pixel_info).color;
}

void	do_not_draw_pixel(t_pixel_info *pixel_info)
{
	(void)pixel_info;
}
