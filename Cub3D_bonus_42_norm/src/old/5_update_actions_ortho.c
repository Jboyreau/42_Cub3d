#include <SDL2/SDL.h>
#include "header.h"

char	ortho_project_zoom_plus(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int 			i = 0, line;

	(*scene).scale += SCALE_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		line = (*((*scene).cloud + i)).y * (*scene).scale + MIDLE_Y;
		line = (line << 10) + (line << 8);
		pixel_info.scene = scene;
		pixel_info.cell = line;
		pixel_info.cell += (*((*scene).cloud + i)).x * (*scene).scale + MIDLE_X;
		(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	ortho_project_zoom_minus(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int 			i = 0, line;

	(*scene).scale -= SCALE_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		line = (*((*scene).cloud + i)).y * (*scene).scale + MIDLE_Y;
		line = (line << 10) + (line << 8);
		pixel_info.scene = scene;
		pixel_info.cell = line;
		pixel_info.cell += (*((*scene).cloud + i)).x * (*scene).scale + MIDLE_X;
		(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	ortho_project(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int				i = 0, line;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		line = (*((*scene).cloud + i)).y * (*scene).scale + MIDLE_Y;
		line = (line << 10) + (line << 8);
		pixel_info.scene = scene;
		pixel_info.cell = line;
		pixel_info.cell += (*((*scene).cloud + i)).x * (*scene).scale + MIDLE_X;
		(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}
