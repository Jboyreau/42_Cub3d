/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_back_face_culling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:27:54 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 00:31:35 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float	is_visible(t_scene *scene, int i)
{
	t_ptri	face;
	t_v3	vecab;
	t_v3	vecac;
	t_v3	normal;
	t_v3	camera_ray;

	face = *((*scene).projected_triangle + i);
	vecab = vec3_subtract(&(face.b), &(face.a));
	vecac = vec3_subtract(&(face.c), &(face.a));
	normal = vec3_cross(&vecab, &vecac);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*scene).origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*scene).dot = vec3_dot(&camera_ray, &normal);
	vec3_normalize(&normal);
	return ((*scene).dot);
}
