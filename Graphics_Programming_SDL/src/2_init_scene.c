#include "header.h"

t_scene	*initialize_scene(int *color_buffer, t_f *fun)
{
	static t_scene	scene;
	//static t_v3	cloud[CUBE_SIZE];
	//static t_tri	triangle_index[CUBE_N_TRI];
	//static t_ptri	projected_triangle[CUBE_N_TRI];
	scene.color_buffer = color_buffer;
	scene.z_buffer = malloc(BUFF_SIZE * sizeof(float));
	if (scene.z_buffer == NULL)
		return (NULL);
	scene.scale = SCALE;
	scene.fun = fun;
	scene.origin.x = 0;
	scene.origin.y = 0;
	scene.origin.z = 0;
	scene.camera.position.x = X_VALUE;
	scene.camera.position.y = Y_VALUE;
	scene.camera.position.z = Z_VALUE;
	scene.camera.rotation.x = 0;
	scene.camera.rotation.y = 0;
	scene.camera.rotation.z = 0;
	scene.pos_incx = X_VALUE;
	scene.pos_incy = Y_VALUE;
	scene.pos_incz = Z_VALUE;
	if (populate_3d_space(&scene) == 0)
		return (NULL);
	return (&scene);
}
