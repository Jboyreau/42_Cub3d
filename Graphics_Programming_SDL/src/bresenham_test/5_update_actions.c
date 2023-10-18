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

void	clear_color_buffer(long long int *color_buffer)
{
	int	i = 0;

	while (i < CLEAR_SIZE)
	{
		*(color_buffer + i) = 0;
		++i;
	}
}
/*
void	clear_color_buffer(int *color_buffer)
{
	int i = 0, j = 1, line, test;

	while (i < WIDTH)
	{
		*(color_buffer + i) = 0x00808080;
		++i;
	}
	i = 1;
	while (i < HEIGHT)
	{
		j = 1;
		line = (i << 10) + (i << 8);
		*(color_buffer + line) = 0x00808080;
		while (j < WIDTH)
		{
			test = (((i + 1) % G == 0) || ((j + 1) % G == 0));
			*(color_buffer + line + j) =  (test << 7) + (test << 15) + (test << 23);
			++j;
		}
		i++;
	}
}*/
