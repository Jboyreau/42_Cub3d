#include <SDL2/SDL.h>
#include "header.h"
#define G 20
#define MODEL_SIZE 729
#define MIDLE_X 640
#define MIDLE_Y 360

char	nothing(t_scene *scene)
{
	(void)scene;
	return (1);
}

char	quit(t_scene *scene)
{
	(void)scene;
	return (0);
}

void	clear_color_buffer(int *color_buffer)
{
	int i = 0, j = 1, line;

	while (i < WIDTH)
	{
		*(color_buffer + i) = 0x00333333;
		++i;
	}
	i = 1;
	while (i < HEIGHT)
	{
		j = 1;
		line = (i << 10) + (i << 8);
		*(color_buffer + line) = 0x00333333;
		while (j < WIDTH)
		{
			*(color_buffer + line + j) = (((i + 1) % G == 0) || ((j + 1) % G == 0)) * 0x00333333;
			++j;
		}
		i++;
	}
}

char ortho_project_zoom_plus(t_scene *scene)
{
	int i = 0, line;

	(*scene).zoom += ZOOM;
	clear_color_buffer((*scene).color_buffer);
	while (i < MODEL_SIZE)
	{
		line = ((*((*scene).cloud + i)).y * (*scene).zoom) + MIDLE_Y;
		line = (line << 10) + (line << 8);
		*((*scene).color_buffer + line + ((int)((*((*scene).cloud + i)).x * (*scene).zoom) + MIDLE_X)) = 0x0000FF00;
		++i;
	}
	return (1);
}

char ortho_project_zoom_minus(t_scene *scene)
{
	int i = 0, line;

	(*scene).zoom -= ZOOM;
	clear_color_buffer((*scene).color_buffer);
	while (i < MODEL_SIZE)
	{
		line = ((*((*scene).cloud + i)).y * (*scene).zoom) + MIDLE_Y;
		line = (line << 10) + (line << 8);
		*((*scene).color_buffer + line + ((int)((*((*scene).cloud + i)).x * (*scene).zoom) + MIDLE_X)) = 0x0000FF00;
		++i;
	}
	return (1);
}

char ortho_project(t_scene *scene)
{
	int i = 0, line;

	clear_color_buffer((*scene).color_buffer);
	while (i < MODEL_SIZE)
	{
		line = ((*((*scene).cloud + i)).y * (*scene).zoom) + MIDLE_Y;
		line = (line << 10) + (line << 8);
		*((*scene).color_buffer + line + ((int)((*((*scene).cloud + i)).x * (*scene).zoom) + MIDLE_X)) = 0x0000FF00;
		++i;
	}
	return (1);
}
