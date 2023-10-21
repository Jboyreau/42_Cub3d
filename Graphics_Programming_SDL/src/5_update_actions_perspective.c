#include <SDL2/SDL.h>
#include "header.h"
#include <stdio.h>

static t_v3	vertex_to_color_buffer(t_scene *scene, t_v3 *vertex, int i_cloud)
{
	float			inv_z;
	inv_z = 1 / ((*((*scene).cloud + i_cloud)).z + (*scene).dist);
	(*vertex).x = ((*((*scene).cloud + i_cloud)).x * (*scene).scale) * inv_z + MIDLE_X;
	(*vertex).y = ((*((*scene).cloud + i_cloud)).y * (*scene).scale) * inv_z + MIDLE_Y;
	(*vertex).z = (*((*scene).cloud + i_cloud)).z;
	return (*vertex);
}

void	triangle_to_color_buffer(t_scene *scene, int i, t_pixel_info *pixel_info)
{
	t_v3	vertex;

	vertex = vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).a, (*((*scene).triangle_index + i)).a - 1);
	(*pixel_info).cell = vertex.x + ((int)(vertex.y) << 10) + ((int)(vertex.y) << 8);
	(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
	//TODO: bresenham

	vertex = vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).b, (*((*scene).triangle_index + i)).b - 1);
	(*pixel_info).cell = vertex.x + ((int)(vertex.y) << 10) + ((int)(vertex.y) << 8);
	(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
	//TODO: bresenham

	vertex = vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).c, (*((*scene).triangle_index + i)).c - 1);
	(*pixel_info).cell = vertex.x + ((int)(vertex.y) << 10) + ((int)(vertex.y) << 8);
	(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);	
	//TODO: bresenham
}

char	perspective_project_close(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int 			i = 0;

	(*scene).dist -= DIST_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	pixel_info.scene = scene;
	while (i < N_TRI)
	{
		triangle_to_color_buffer(scene, i, &pixel_info);
		//(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	perspective_project_far(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int 			i = 0;

	(*scene).dist += DIST_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	pixel_info.scene = scene;
	while (i < N_TRI)
	{
		triangle_to_color_buffer(scene, i, &pixel_info);
		//(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	perspective_project_zoom_plus(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int 			i = 0;

	(*scene).scale += SCALE_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	pixel_info.scene = scene;
	while (i < N_TRI)
	{
		triangle_to_color_buffer(scene, i, &pixel_info);
		//(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	perspective_project_zoom_minus(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int 			i = 0;

	(*scene).scale -= SCALE_INC;
	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	pixel_info.scene = scene;
	while (i < N_TRI)
	{
		triangle_to_color_buffer(scene, i, &pixel_info);
		//(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}

char	perspective_project(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int				i = 0;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)));
	pixel_info.scene = scene;
	while (i < N_TRI)
	{
		triangle_to_color_buffer(scene, i, &pixel_info);
		//(*(*scene).fun).fun_draw_pixel[(pixel_info.cell > 0 && pixel_info.cell < BUFF_SIZE)](&pixel_info);
		++i;
	}
	return (1);
}
