/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_triangle_to_color_buffer2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:47:40 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 17:04:34 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	vertex_to_color_buffer(t_scene *scene, t_v3 *vertex)
{
	(*vertex).inv_z = 1 / (*vertex).z;
	(*vertex).x = ((*vertex).x * (*scene).scale) * (*vertex).inv_z + MIDLE_X;
	(*vertex).y = ((*vertex).y * (*scene).scale) * (*vertex).inv_z + MIDLE_Y;
}

void	init_screen_space_normals(t_ptri *face)
{
	t_v3	vec1;
	t_v3	vec2;
	t_v3	normal;

	vec1 = vec3_subtract(&((*face).b), &((*face).a));
	vec2 = vec3_subtract(&((*face).c), &((*face).a));
	normal = vec3_cross(&vec1, &vec2);
	(*face).p0.normal = normal;
	vec1 = vec3_subtract(&((*face).c), &((*face).b));
	vec2 = vec3_subtract(&((*face).a), &((*face).b));
	normal = vec3_cross(&vec1, &vec2);
	(*face).p1.normal = normal;
	vec1 = vec3_subtract(&((*face).a), &((*face).c));
	vec2 = vec3_subtract(&((*face).b), &((*face).c));
	normal = vec3_cross(&vec1, &vec2);
	(*face).p2.normal = normal;
}
