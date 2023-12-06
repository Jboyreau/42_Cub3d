/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:13:10 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 17:50:31 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	populate_map(t_scene *scene)
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

static void	init_value(t_scene *scene)
{
	(*scene).origin.x = 0;
	(*scene).origin.y = 0;
	(*scene).origin.z = 0;
	(*scene).rotation.x = 0;
	(*scene).rotation.y = 0;
	(*scene).rotation.z = 0;
	(*scene).pos_incx = X_VALUE;
	(*scene).pos_incy = Y_VALUE;
	(*scene).pos_incz = Z_VALUE;
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
	init_value(&scene);
	init_camera(&scene);
	init_plane(&scene);
	scene.poly = poly;
	scene.inside_vertices = inside_vertices;
	if (populate_map(&scene) == 0)
		return (free(scene.z_buffer), NULL);
	if (load_all_texture(&scene) == 0)
		return (free(scene.z_buffer), NULL);
	return (&scene);
}
