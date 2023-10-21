#include <SDL2/SDL.h>
#include "header.h"

t_scene	*initialize_scene(int *color_buffer, t_f *fun)
{
	static t_scene	scene;
	static t_v3		cloud[MODEL_SIZE];
	static t_tri	triangle_index[N_TRI];
	static t_ptri	projected_triangle[N_TRI];

	scene.cloud = cloud;
	scene.triangle_index = triangle_index;
	scene.projected_triangle = projected_triangle;
	scene.color_buffer = color_buffer;
	scene.scale = SCALE;
	scene.fun = fun;
	scene.dist = Z_VALUE;
	//scene.rotation.x = 0;
	//scene.rotation.y = 0;
	//scene.rotation.z = 0;
	populate_3d_space(cloud, triangle_index);
	return (&scene);
}
