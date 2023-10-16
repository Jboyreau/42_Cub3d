#include <SDL2/SDL.h>
#include <stdio.h>
#include "header.h"

void	make_cube(t_v3 *cube)
{
	int page = 0, line = 0, col = 0, p, l;
	t_v3	vec;

	vec.z = -1;
	while (page < 9)
	{
		vec.y = -1;
		line = 0;
		p = page * 81;
		while (line < 9)
		{
			vec.x = -1;
			col = 0;
			l = p + line * 9;
			while (col < 9)
			{
				(*(cube + l + col)).x = vec.x;
				(*(cube + l + col)).y = vec.y;
				(*(cube + l + col)).z = vec.z;
				(*(cube + l + col)).inv_z = 1;
				++col;
				vec.x += 0.25;
			}
			++line;
			vec.y += 0.25;
		}
		++page;
		vec.z += 0.25;
	}
}
