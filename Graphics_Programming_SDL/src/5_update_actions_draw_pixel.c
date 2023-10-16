#include <SDL2/SDL.h>
#include "header.h"

void	draw_pixel(t_pixel_info *pixel_info)
{
	*((*(*pixel_info).scene).color_buffer + (*pixel_info).cell) = 0x0000FF00;
}

void	do_not_draw_pixel(t_pixel_info *pixel_info)
{
	(void)pixel_info;
}
