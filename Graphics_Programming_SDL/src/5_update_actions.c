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
	int i = 0, j = 1, line, test;

	while (i < WIDTH)
	{
		*(color_buffer + i) = 0x000F0F0F;
		++i;
	}
	i = 1;
	while (i < HEIGHT)
	{
		j = 1;
		line = (i << 10) + (i << 8);
		*(color_buffer + line) = 0x000F0F0F;
		while (j < WIDTH)
		{
			test = (((i + 1) % G == 0) || ((j + 1) % G == 0));
			*(color_buffer + line + j) =  (test << 4) + (test << 11) + (test << 19);
			++j;
		}
		i++;
	}
}
