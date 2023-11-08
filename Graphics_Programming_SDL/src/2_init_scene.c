#include "header.h"

static void	init_camera(t_scene *scene)
{
	(*scene).camera.position.x = X_VALUE;
	(*scene).camera.position.y = Y_VALUE;
	(*scene).camera.position.z = Z_VALUE;
	(*scene).camera.fov_w = 2.0 * atan((double)WIDTH / 2.0);
	(*scene).camera.fov_h = 2.0 * atan((double)HEIGHT / 2.0);
	(*scene).camera.rotation.x = 0;
	(*scene).camera.rotation.y = 0;
	(*scene).camera.rotation.z = 0;
}

static void	init_plane(t_scene *scene)
{
	static t_v3	origin = {0, 0, 0, 0};

	(*scene).view.near.point = origin;
	(*scene).view.far.point.z = Z_MIN;
	(*scene).view.near.n.x = 0;
	(*scene).view.near.n.y = 0;
	(*scene).view.near.n.z = 1;
	(*scene).view.near.point = origin;
	(*scene).view.far.point.z = Z_MAX;
	(*scene).view.far.n.x = 0;
	(*scene).view.far.n.y = 0;
	(*scene).view.far.n.z = -1;
	(*scene).view.right.point = origin;
	(*scene).view.right.n.x = -cos((*scene).camera.fov_w / 2);
	(*scene).view.right.n.y = 0;
	(*scene).view.right.n.z = sin((*scene).camera.fov_w / 2);
	(*scene).view.left.point = origin;
	(*scene).view.left.n.x = cos((*scene).camera.fov_w / 2);
	(*scene).view.left.n.y = 0;
	(*scene).view.left.n.z = sin((*scene).camera.fov_w / 2);
	(*scene).view.top.point = origin;
	(*scene).view.top.n.x = 0;
	(*scene).view.top.n.y = -cos((*scene).camera.fov_h / 2);
	(*scene).view.top.n.z = sin((*scene).camera.fov_h / 2);
	(*scene).view.bottom.point = origin;
	(*scene).view.bottom.n.x = 0;
	(*scene).view.bottom.n.y = cos((*scene).camera.fov_h / 2);
	(*scene).view.bottom.n.z = sin((*scene).camera.fov_h / 2);
}

t_scene	*initialize_scene(int *color_buffer, t_f *fun)
{
	static t_scene	scene;

	scene.color_buffer = color_buffer;
	scene.z_buffer = malloc(BUFF_SIZE * sizeof(float));
	if (scene.z_buffer == NULL)
		return (NULL);
	scene.scale = SCALE;
	scene.fun = fun;
	scene.origin.x = 0;
	scene.origin.y = 0;
	scene.origin.z = 0;
	init_camera(&scene);
	init_plane(&scene);
	scene.rotation.x = 0;
	scene.rotation.y = 0;
	scene.rotation.z = 0;
	scene.pos_incx = X_VALUE;
	scene.pos_incy = Y_VALUE;
	scene.pos_incz = Z_VALUE;
	scene.radius = 0;
	if (populate_3d_space(&scene) == 0)
		return (NULL);
	return (&scene);
}
