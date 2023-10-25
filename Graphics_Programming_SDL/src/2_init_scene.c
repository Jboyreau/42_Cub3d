#include "header.h"

t_scene	*initialize_scene(int *color_buffer, t_f *fun)
{
	static t_scene	scene;
	//static t_v3	cloud[CUBE_SIZE];
	//static t_tri	triangle_index[CUBE_N_TRI];
	//static t_ptri	projected_triangle[CUBE_N_TRI];
	scene.color_buffer = color_buffer;
	scene.scale = SCALE;
	scene.fun = fun;
	scene.dist = Z_VALUE;
	scene.camera.position.x = 0;
	scene.camera.position.y = 0;
	scene.camera.position.z = 0;
	//scene.rotation.x = 0;
	//scene.rotation.y = 0;
	//scene.rotation.z = 0;
	if (populate_3d_space(&scene) == 0)
		return (NULL);
	return (&scene);
}
