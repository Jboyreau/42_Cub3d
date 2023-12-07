/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_triangle_to_color_buffer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:35:17 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 17:02:08 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	triangle_to_color_buffer4(t_scene *scene,
int i, t_pixel_info *pixel_info)
{	
	init_screen_space_normals((*scene).projected_triangle + i);
	(*pixel_info).screen_space_p0 = (*((*scene).projected_triangle + i)).p0;
	(*pixel_info).screen_space_p1 = (*((*scene).projected_triangle + i)).p1;
	(*pixel_info).screen_space_p2 = (*((*scene).projected_triangle + i)).p2;
	launch(scene, pixel_info, i);
}

static void	triangle_to_color_buffer3(t_scene *scene,
int i, t_pixel_info *pixel_info)
{
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).c);
	(*((*scene).projected_triangle
				+ i)).p2.x = (*((*scene).projected_triangle + i)).c.x;
	(*((*scene).projected_triangle
				+ i)).p2.fx = (*((*scene).projected_triangle + i)).c.x;
	(*((*scene).projected_triangle
				+ i)).p2.y = (*((*scene).projected_triangle + i)).c.y;
	(*((*scene).projected_triangle
				+ i)).p2.fy = (*((*scene).projected_triangle + i)).c.y;
	(*((*scene).projected_triangle
				+ i)).p2.z = (*((*scene).projected_triangle + i)).c.z;
	(*((*scene).projected_triangle
				+ i)).p2.inv_z = (*((*scene).projected_triangle + i)).c.inv_z;
	triangle_to_color_buffer4(scene, i, pixel_info);
}

static void	triangle_to_color_buffer2(t_scene *scene,
int i, t_pixel_info *pixel_info)
{
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).b);
	(*((*scene).projected_triangle
				+ i)).p1.x = (*((*scene).projected_triangle + i)).b.x;
	(*((*scene).projected_triangle
				+ i)).p1.fx = (*((*scene).projected_triangle + i)).b.x;
	(*((*scene).projected_triangle
				+ i)).p1.y = (*((*scene).projected_triangle + i)).b.y;
	(*((*scene).projected_triangle
				+ i)).p1.fy = (*((*scene).projected_triangle + i)).b.y;
	(*((*scene).projected_triangle
				+ i)).p1.z = (*((*scene).projected_triangle + i)).b.z;
	(*((*scene).projected_triangle
				+ i)).p1.inv_z = (*((*scene).projected_triangle + i)).b.inv_z;
	triangle_to_color_buffer3(scene, i, pixel_info);
}

void	triangle_to_color_buffer(t_scene *scene,
int i, t_pixel_info *pixel_info)
{
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).a);
	(*((*scene).projected_triangle
				+ i)).p0.x = (*((*scene).projected_triangle + i)).a.x;
	(*((*scene).projected_triangle
				+ i)).p0.fx = (*((*scene).projected_triangle + i)).a.x;
	(*((*scene).projected_triangle
				+ i)).p0.y = (*((*scene).projected_triangle + i)).a.y;
	(*((*scene).projected_triangle
				+ i)).p0.fy = (*((*scene).projected_triangle + i)).a.y;
	(*((*scene).projected_triangle
				+ i)).p0.z = (*((*scene).projected_triangle + i)).a.z;
	(*((*scene).projected_triangle
				+ i)).p0.inv_z = (*((*scene).projected_triangle + i)).a.inv_z;
	triangle_to_color_buffer2(scene, i, pixel_info);
}
