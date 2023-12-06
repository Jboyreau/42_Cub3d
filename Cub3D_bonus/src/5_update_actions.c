#include "header.h"
#define G 20

char	nothing(t_scene *scene)
{
	(void)scene;
	return (1);
}

void	clear_color_buffer(long long int *color_buffer, float *z_buffer)
{
	int	i = 0;

	while (i < CLEAR_SIZE)
	{
		*(z_buffer + i) = (float)0xffffffff;
		*(color_buffer + i) = 0;
		++i;
	}
	while (i < BUFF_SIZE)
	{
		*(z_buffer + i) = (float)0xffffffff;
		++i;
	}
}
