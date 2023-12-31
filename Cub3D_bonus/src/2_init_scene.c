#include "header.h"

static void	init_camera(t_scene *scene)
{
	(*scene).camera.position.x = X_VALUE;
	(*scene).camera.position.y = Y_VALUE;
	(*scene).camera.position.z = Z_VALUE;
	(*scene).camera.fov_w = 1.135;
	(*scene).camera.fov_h = 0.68;
	(*scene).camera.rotation.x = 0;
	(*scene).camera.rotation.y = 0;
	(*scene).camera.rotation.z = 0;
}

static void	init_plane(t_scene *scene)
{
	static t_v3	origin = {0, 0, 0, 0};
	float		fov_h;
	float		fov_w;

	fov_h = (*scene).camera.fov_h / 2;
	fov_w = (*scene).camera.fov_w / 2;
	tv3_uv(&(*scene).view.near.point, &origin);
	(*scene).view.near.point.z = Z_MIN;
	(*scene).view.near.n.x = 0;
	(*scene).view.near.n.y = 0;
	(*scene).view.near.n.z = 1;
	tv3_uv(&(*scene).view.far.point, &origin);
	(*scene).view.far.point.z = Z_MAX;
	(*scene).view.far.n.x = 0;
	(*scene).view.far.n.y = 0;
	(*scene).view.far.n.z = -1;
	tv3_uv(&(*scene).view.right.point, &origin);
	(*scene).view.right.n.x = -cos(fov_w);
	(*scene).view.right.n.y = 0;
	(*scene).view.right.n.z = sin(fov_w);
	tv3_uv(&(*scene).view.left.point, &origin);
	(*scene).view.left.n.x = cos(fov_w);
	(*scene).view.left.n.y = 0;
	(*scene).view.left.n.z = sin(fov_w);
	tv3_uv(&(*scene).view.top.point, &origin);
	(*scene).view.top.n.x = 0;
	(*scene).view.top.n.y = cos(fov_h);
	(*scene).view.top.n.z = sin(fov_h);
	tv3_uv(&(*scene).view.bottom.point, &origin);
	(*scene).view.bottom.n.x = 0;
	(*scene).view.bottom.n.y = -cos(fov_h);
	(*scene).view.bottom.n.z = sin(fov_h);
}

void	affect_wall(t_scene *scene)
{
	(*scene).cloud_size_wall = (*scene).cloud_size_temp;
	(*scene).triangle_index_size_wall = (*scene).triangle_index_size_temp;
	(*scene).cloud_wall = (*scene).cloud_temp;
	(*scene).triangle_index_wall = (*scene).triangle_index_temp;
}

void	affect_floor(t_scene *scene)
{
	(*scene).cloud_size_floor = (*scene).cloud_size_temp;
	(*scene).triangle_index_size_floor = (*scene).triangle_index_size_temp;
	(*scene).cloud_floor = (*scene).cloud_temp;
	(*scene).triangle_index_floor = (*scene).triangle_index_temp;
}

void	affect_roof(t_scene *scene)
{
	(*scene).cloud_size_roof = (*scene).cloud_size_temp;
	(*scene).triangle_index_size_roof = (*scene).triangle_index_size_temp;
	(*scene).cloud_roof = (*scene).cloud_temp;
	(*scene).triangle_index_roof = (*scene).triangle_index_temp;
}

static int populate_map(t_scene *scene)
{
	(*scene).obj_path = OBJ_WALL;
	(*scene).part = TYPE_WALL;
	if (populate_3d_space(scene) == 0)
		return (0);
	affect_wall(scene);
	(*scene).obj_path = OBJ_FLOOR;
	(*scene).part = TYPE_FLOOR;
	if (populate_3d_space(scene) == 0)
		return (0);
	affect_floor(scene);
	(*scene).obj_path = OBJ_ROOF;
	(*scene).part = TYPE_ROOF;
	if (populate_3d_space(scene) == 0)
		return (0);
	affect_roof(scene);
	if (assemble_map(scene) == 0)
		return (0);
	return (1);
}

static int	load_all_texture(t_scene *scene)
{
	if (load_texture((*scene).tso, scene, SOUTH) == 0)
		return (0);
	if (load_texture((*scene).tno, scene, NORTH) == 0)
		return (0);
	if (load_texture((*scene).tea, scene, EAST) == 0)
		return (0);
	if (load_texture((*scene).twe, scene, WEST) == 0)
		return (0);
	if (load_texture((*scene).tf, scene, FLOOR) == 0)
		return (0);
	if (load_texture((*scene).tr, scene, ROOF) == 0)
		return (0);
	return (1);
}

t_scene	*initialize_scene(t_f *fun, char *map_path)
{
	static t_scene	scene;
	static t_v3_uv	poly[POLY_SIZE];
	static t_v3_uv	inside_vertices[POLY_SIZE];

	scene.map_path = map_path;
	scene.color_buffer = malloc(sizeof(int) * BUFF_SIZE);
	if (scene.color_buffer == NULL)
		return (NULL);
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
	scene.poly = poly;
	scene.inside_vertices = inside_vertices;
	if (populate_map(&scene) == 0)
		return (free(scene.z_buffer), NULL);
	if (load_all_texture(&scene) == 0)
		return (free(scene.z_buffer), NULL);
	return (&scene);
}
