#include <SDL2/SDL.h>
#include "header.h"

void	initialize_scene(t_scene *scene, t_v3 *cloud, int *color_buffer, int zoom)
{
	make_cube(cloud);
	(*scene).cloud = cloud;
	(*scene).color_buffer = color_buffer;
	(*scene).zoom = zoom;
}
