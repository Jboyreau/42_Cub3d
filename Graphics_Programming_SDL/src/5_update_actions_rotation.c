#include <SDL2/SDL.h>
#include <math.h>
#include "header.h"
#include <stdio.h>

static void	 project(t_scene *scene, t_v3 *cloud)
{
	int				line;
	t_pixel_info	pixel_info;
	float			inv_z;

	inv_z = 1 / ((*cloud).z + (*scene).dist);
	line = ((*cloud).y * (*scene).scale) * inv_z + MIDLE_Y;
	line = (line << 10) + (line << 8);
	pixel_info.scene = scene;
	pixel_info.cell = line;
	pixel_info.cell += ((*cloud).x * (*scene).scale) * inv_z + MIDLE_X;
	(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
}

char	rotation_x_minus(t_scene *scene)
{
	float y, z;
	int		i = 0;

	clear_color_buffer((*scene).color_buffer);
	while (i < MODEL_SIZE)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z; //printf("x = %f\n", (*((*scene).cloud + i)).x);
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) - y * sin(ROTATION_INC_MINUS); //printf("y = %f\n", (*((*scene).cloud + i)).z);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_MINUS) + z * sin(ROTATION_INC_MINUS); //printf("z = %f\n", (*((*scene).cloud + i)).y);
		project(scene, (*scene).cloud + i);
		++i;
	}
	return (1);
}

char	rotation_x_plus(t_scene *scene)
{
	float y, z;
	int		i = 0;

	clear_color_buffer((*scene).color_buffer);
	while (i < MODEL_SIZE)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) - y * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_PLUS) + z * sin(ROTATION_INC_PLUS);
		project(scene, (*scene).cloud + i);
		++i;
	}
	return (1);
}

char	rotation_y_minus(t_scene *scene)
{
	float x, z;
	int		i = 0;

	clear_color_buffer((*scene).color_buffer);
	while (i < MODEL_SIZE)
	{
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) + x * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_MINUS) - z * sin(ROTATION_INC_MINUS);
		project(scene, (*scene).cloud + i);
		++i;
	}
	
	return (1);
}

char	rotation_y_plus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	clear_color_buffer((*scene).color_buffer);
	while (i < MODEL_SIZE)
	{
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_PLUS) - z * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) + x * sin(ROTATION_INC_PLUS);
		project(scene, (*scene).cloud + i);
		++i;
	}
	return (1);
}
