/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_draw_pixel2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:12:43 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 22:10:46 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_v3	init_face(t_v2 *a, float az)
{
	t_v3	p;

	p.x = (*a).x;
	p.y = (*a).y;
	p.z = az;
	return (p);
}

t_v3	calcultate_interpolated_normal(t_pixel_info *pixel_info)
{
	t_v3	int_normal;

	int_normal.x = (*pixel_info).weight.x * (*pixel_info).p0.normal.x
		+ (*pixel_info).weight.y * (*pixel_info).p1.normal.x
		+ (*pixel_info).weight.z * (*pixel_info).p2.normal.x;
	int_normal.y = (*pixel_info).weight.x * (*pixel_info).p0.normal.y
		+ (*pixel_info).weight.y * (*pixel_info).p1.normal.y
		+ (*pixel_info).weight.z * (*pixel_info).p2.normal.y;
	int_normal.z = (*pixel_info).weight.x * (*pixel_info).p0.normal.z
		+ (*pixel_info).weight.y * (*pixel_info).p1.normal.z
		+ (*pixel_info).weight.z * (*pixel_info).p2.normal.z;
	return (int_normal);
}

void	dot(t_pixel_info *pixel_info)
{
	t_v3	p;
	t_v3	normal;
	t_v3	camera_ray;

	p = init_face(&(*pixel_info).p, (*pixel_info).interpolated.w);
	normal = calcultate_interpolated_normal(pixel_info);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*pixel_info).screen_space_origin), &p);
	vec3_normalize(&camera_ray);
	(*pixel_info).dot = vec3_dot(&camera_ray, &normal);
	if ((*pixel_info).dot < 0.35
		|| isnanf((*pixel_info).dot)
		|| isinf((*pixel_info).dot)
		|| (*pixel_info).dot > 1)
		(*pixel_info).dot = 0.35;
}
