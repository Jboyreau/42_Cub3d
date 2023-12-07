/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_perspective.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:58:00 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 18:57:41 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	triangle_to_nowhere(t_scene *scene, int i, t_pixel_info *pixel_info)
{
	(void)scene;
	(void)i;
	(void)pixel_info;
}

char	camera_perspective_project(t_scene *scene)
{
	t_pixel_info	*pixel_info;
	int				j;
	int				i;

	pixel_info = &((*((t_arg *)(*scene).arg)).pixel_info);
	clear_color_buffer(((long long int *)((*scene).color_buffer)),
		(*scene).z_buffer);
	(*pixel_info).scene = scene;
	i = -1;
	while (++i < (*scene).triangle_index_size)
	{
		poly_to_tri(scene, tri_to_poly(scene, (*scene).triangle_index + i));
		(*pixel_info).texture = (*((*scene).triangle_index + i)).texture;
		j = -1;
		while (++j < (*scene).nb_tri)
			(*(*scene).fun).culling[
				(is_visible(scene, j) > 0)](scene, j, pixel_info);
	}
	return (1);
}

int	test(t_scene *s, t_pixel_info **pixel_info, int *index)
{
	int		i;
	int		condition;
	float	next_x;
	float	next_y;
	float	next_z;

	*pixel_info = &((*((t_arg *)(*s).arg)).pixel_info);
	clear_color_buffer(((long long int *)((*s).color_buffer)), (*s).z_buffer);
	(**pixel_info).scene = s;
	*index = -1;
	i = -1;
	condition = 0;
	while (++i < (*s).wall_last_index && condition == 0)
	{
		next_x = (*((*s).cloud + i)).x + (*s).pos_incx;
		next_y = (*((*s).cloud + i)).y + (*s).pos_incy;
		next_z = (*((*s).cloud + i)).z + (*s).pos_incz;
		condition = (((next_x > -3 && next_x < 3))
				&& ((next_y > -3 && next_y < 3))
				&& ((next_z > -3 && next_z < 3)));
	}
	return (condition);
}

char	perspective_project(t_scene *s)
{
	t_pixel_info	*pixel_info;
	int				condition;
	int				i;
	int				j;

	pixel_info = NULL;
	condition = test(s, &pixel_info, &i);
	while (++i < (*s).cloud_size && condition == 0)
	{
		rev_camera_rotation_x(s, i, -(*s).camera.rotation.x);
		(*((*s).cloud + i)).x += (*s).pos_incx;
		(*((*s).cloud + i)).y += (*s).pos_incy;
		(*((*s).cloud + i)).z += (*s).pos_incz;
		rev_camera_rotation_x(s, i, (*s).camera.rotation.x);
	}
	i = -1;
	while (++i < (*s).triangle_index_size)
	{
		poly_to_tri(s, tri_to_poly(s, (*s).triangle_index + i));
		(*pixel_info).texture = (*((*s).triangle_index + i)).texture;
		j = -1;
		while (++j < (*s).nb_tri)
			(*(*s).fun).culling[(is_visible(s, j) > 0)](s, j, pixel_info);
	}
	return ((*s).pos_incx = 0, (*s).pos_incy = 0, (*s).pos_incz = 0, 1);
}
