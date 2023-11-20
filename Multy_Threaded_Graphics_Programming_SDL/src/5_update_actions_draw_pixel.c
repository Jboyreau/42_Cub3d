#include "header.h"

void	draw_pixel(t_pixel_info *pixel_info)
{
	int a;
	int r;
	int g;
	int b;
	a = 0xFF000000;
	r = ((*pixel_info).color & 0x00FF0000) * (*(*pixel_info).scene).dot;
	g = ((*pixel_info).color & 0x0000FF00) * (*(*pixel_info).scene).dot;
	b = ((*pixel_info).color & 0x000000FF) * (*(*pixel_info).scene).dot;
	*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) = (*pixel_info).depth;
	*((*(*pixel_info).scene).color_buffer + (*pixel_info).cell) = 
		a 
		| (r & 0x00FF0000)
		| (g & 0x0000FF00)
		| (b & 0x000000FF);
}

void	do_not_draw_pixel(t_pixel_info *pixel_info)
{
	(void)pixel_info;
}
