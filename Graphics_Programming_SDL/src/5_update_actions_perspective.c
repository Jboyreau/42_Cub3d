#include <SDL2/SDL.h>
#include "header.h"
#include <stdio.h>

static void	vertex_to_color_buffer(t_scene *scene, t_v3 *vertex, int i_cloud)
{
	float			inv_z;

	inv_z = 1 / ((*((*scene).cloud + i_cloud)).z + (*scene).dist);
	(*vertex).x = ((*((*scene).cloud + i_cloud)).x * (*scene).scale) * inv_z + MIDLE_X;
	(*vertex).y = ((*((*scene).cloud + i_cloud)).y * (*scene).scale) * inv_z + MIDLE_Y;
	(*vertex).z = (*((*scene).cloud + i_cloud)).z;
}

void	triangle_to_color_buffer(t_scene *scene, int i, t_pixel_info *pixel_info)
{
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).a, (*((*scene).triangle_index + i)).a - 1);
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).b, (*((*scene).triangle_index + i)).b - 1);
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).c, (*((*scene).triangle_index + i)).c - 1);
	draw_triangle(scene, pixel_info, i);
}

char	perspective_project(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int				i = -1;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	pixel_info.scene = scene;
	while (++i < N_TRI)
		triangle_to_color_buffer(scene, i, &pixel_info);
	return (1);
}

char	perspective_project_close(t_scene *scene)
{
	(*scene).dist -= DIST_INC;
	return (perspective_project(scene));
}

char	perspective_project_far(t_scene *scene)
{
	(*scene).dist += DIST_INC;
	return (perspective_project(scene));
}

char	perspective_project_zoom_plus(t_scene *scene)
{
	(*scene).scale += SCALE_INC;
	return (perspective_project(scene));
}

char	perspective_project_zoom_minus(t_scene *scene)
{
	(*scene).scale -= SCALE_INC;
	return (perspective_project(scene));
}
