#include <SDL2/SDL.h>
#include "header.h"

t_scene	*initialize_scene(t_v3 *cloud, int *color_buffer, int scale, t_f *fun)
{
	static t_scene	scene;

	scene.cloud = cloud;
	scene.color_buffer = color_buffer;
	scene.scale = scale;
	scene.fun = fun;
	make_cube(cloud);
	return (&scene);
}
