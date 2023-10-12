#include <SDL2/SDL.h>
#include "header.h"

char	nothing(int *color_buffer)
{
	(void)color_buffer;
	return (1);
}

char	quit(int *color_buffer)
{	
	(void)color_buffer;
	return (0);
}

void	clear_color_buffer(long long int *color_buffer)
{
	int i = 0;

	while (i < CLEAR_SIZE)
	{
		*(color_buffer + i) = 0;
		++i;
	}
}

char	circle(int *color_buffer)
{
	int i = 160, j, line, x, y, r = 200 * 200;

	clear_color_buffer((long long int*)color_buffer);
	while (i < 560)
	{
		j = 440;
		line = i * WIDTH;
		y = i - 360;
		if (y < 0)
			y *= -1;
		while (j < 840)
		{
			x = j - 640;
			if (x < 0)
				x *= -1;
			if ((x * x + y * y) <= r)
				*(color_buffer + line + j) = 0xFFFF0000;
			//else
				//*(color_buffer + line + j) = 0xFFFF0000;	
			++j;
		}
		++i;
	}
	return (1);
}

char	square(int *color_buffer)
{
	int i = 0, j, line;
	
	clear_color_buffer((long long int*)color_buffer);
	while (i < HEIGHT)
	{
		j = 0;
		line = i * WIDTH;
		while (j < WIDTH)
		{
			*(color_buffer + line + j) = 0xFFFF0000;
			++j;
		}
		++i;
	}
	return (1);
}
