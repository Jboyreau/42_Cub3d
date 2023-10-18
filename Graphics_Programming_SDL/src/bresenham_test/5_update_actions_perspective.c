#include <SDL2/SDL.h>
#include "header.h"
#include <stdio.h>

char	perspective_project_close(t_scene *scene)
{
	t_pixel_info	pixel_info;
	float			inv_z;
	int 			i = 0, line;


	(*scene).dist -= DIST_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		inv_z = 1 / ((*((*scene).cloud + i)).z + (*scene).dist);
		line = ((*((*scene).cloud + i)).y * (*scene).scale) * inv_z + MIDLE_Y;
		line = (line << 10) + (line << 8);
		pixel_info.scene = scene;
		pixel_info.cell = line;
		pixel_info.cell += ((*((*scene).cloud + i)).x * (*scene).scale) * inv_z + MIDLE_X;
		(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	perspective_project_far(t_scene *scene)
{
	t_pixel_info	pixel_info;
	float			inv_z;
	int 			i = 0, line;

	(*scene).dist += DIST_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		inv_z = 1 / ((*((*scene).cloud + i)).z + (*scene).dist);
		line = ((*((*scene).cloud + i)).y * (*scene).scale) * inv_z + MIDLE_Y;
		line = (line << 10) + (line << 8);
		pixel_info.scene = scene;
		pixel_info.cell = line;
		pixel_info.cell += ((*((*scene).cloud + i)).x * (*scene).scale) * inv_z + MIDLE_X;
		(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	perspective_project_zoom_plus(t_scene *scene)
{
	t_pixel_info	pixel_info;
	float			inv_z;
	int 			i = 0, line;

	(*scene).scale += SCALE_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		inv_z = 1 / ((*((*scene).cloud + i)).z + (*scene).dist);
		line = ((*((*scene).cloud + i)).y * (*scene).scale) * inv_z + MIDLE_Y;
		line = (line << 10) + (line << 8);
		pixel_info.scene = scene;
		pixel_info.cell = line;
		pixel_info.cell += ((*((*scene).cloud + i)).x * (*scene).scale) * inv_z + MIDLE_X;
		(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	perspective_project_zoom_minus(t_scene *scene)
{
	t_pixel_info	pixel_info;
	float			inv_z;
	int 			i = 0, line;

	(*scene).scale -= SCALE_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		inv_z = 1 / ((*((*scene).cloud + i)).z + (*scene).dist);
		line = ((*((*scene).cloud + i)).y * (*scene).scale) * inv_z + MIDLE_Y;
		line = (line << 10) + (line << 8);
		pixel_info.scene = scene;
		pixel_info.cell = line;
		pixel_info.cell += ((*((*scene).cloud + i)).x * (*scene).scale) * inv_z + MIDLE_X;
		(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	perspective_project(t_scene *scene)
{
	t_pixel_info	pixel_info;
	float			inv_z;
	int				i = 0, line;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		inv_z = 1 / ((*((*scene).cloud + i)).z + (*scene).dist);
		line = ((*((*scene).cloud + i)).y * (*scene).scale) * inv_z + MIDLE_Y;
		line = (line << 10) + (line << 8);
		pixel_info.scene = scene;
		pixel_info.cell = line;
		pixel_info.cell += ((*((*scene).cloud + i)).x * (*scene).scale) * inv_z + MIDLE_X;
		(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}
