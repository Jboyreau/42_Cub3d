#include "header.h"

void	draw_pixel(t_pixel_info *pixel_info)
{
	*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) = (*pixel_info).depth;
	*((*(*pixel_info).scene).color_buffer + (*pixel_info).cell) = 
		((*(*pixel_info).scene).dot > 0.8) * 0xFF909090
		+ ((*(*pixel_info).scene).dot <= 0.8 && (*(*pixel_info).scene).dot > 0.7) * 0xFF808080
		+ ((*(*pixel_info).scene).dot <= 0.7 && (*(*pixel_info).scene).dot > 0.6) * 0xFF707070
		+ ((*(*pixel_info).scene).dot <= 0.6 && (*(*pixel_info).scene).dot > 0.5) * 0xFF606060
		+ ((*(*pixel_info).scene).dot <= 0.5 && (*(*pixel_info).scene).dot > 0.4) * 0xFF505050
		+ ((*(*pixel_info).scene).dot <= 0.4 && (*(*pixel_info).scene).dot > 0.3) * 0xFF404040
		+ ((*(*pixel_info).scene).dot <= 0.3 && (*(*pixel_info).scene).dot > 0.2) * 0xFF303030
		+ ((*(*pixel_info).scene).dot <= 0.2 && (*(*pixel_info).scene).dot > 0.1) * 0xFF202020
		+ ((*(*pixel_info).scene).dot <= 0.1 && (*(*pixel_info).scene).dot > 0) * 0xFF101010;
}

void	do_not_draw_pixel(t_pixel_info *pixel_info)
{
	(void)pixel_info;
}
