#include <SDL2/SDL.h>
#include <math.h>
#include "header.h"
#include <stdio.h>

char	rotation_x_minus(t_scene *scene)
{
	float	y, z;
	int		i = 0;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) - y * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_MINUS) + z * sin(ROTATION_INC_MINUS);
		++i;
	}
	perspective_project(scene);
	return (1);
}

char	rotation_x_plus(t_scene *scene)
{
	float	y, z;
	int		i = 0;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) - y * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_PLUS) + z * sin(ROTATION_INC_PLUS);
		++i;
	}	
	perspective_project(scene);
	return (1);
}

char	rotation_y_minus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) + x * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_MINUS) - z * sin(ROTATION_INC_MINUS);
		++i;
	}	
	perspective_project(scene);
	return (1);
}

char	rotation_y_plus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) + x * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_PLUS) - z * sin(ROTATION_INC_PLUS);
		++i;
	}
	perspective_project(scene);
	return (1);
}

char	rotation_z_minus(t_scene *scene)
{
	float	x, y;
	int		i = 0;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		x = (*((*scene).cloud + i)).x;
		y = (*((*scene).cloud + i)).y;
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_MINUS) + y * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_MINUS) - x * sin(ROTATION_INC_MINUS);
		++i;
	}
	perspective_project(scene);	
	return (1);
}

char	rotation_z_plus(t_scene *scene)
{
	float	x, y;
	int		i = 0;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	while (i < MODEL_SIZE)
	{
		x = (*((*scene).cloud + i)).x;
		y = (*((*scene).cloud + i)).y;
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_PLUS) + y * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_PLUS) - x * sin(ROTATION_INC_PLUS);
		++i;
	}
	perspective_project(scene);
	return (1);
}
