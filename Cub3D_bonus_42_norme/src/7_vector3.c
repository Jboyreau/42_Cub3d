/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_vector3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:55:23 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:56:03 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_v3	vec3_cross(t_v3 *a, t_v3 *b)
{
	t_v3	normal;

	normal.x = ((*a).y * (*b).z) - ((*a).z * (*b).y);
	normal.y = ((*a).z * (*b).x) - ((*a).x * (*b).z);
	normal.z = ((*a).x * (*b).y) - ((*a).y * (*b).x);
	return (normal);
}

float	vec2_dot(t_v2 *a, t_v2 *b)
{
	return (((*a).x * (*b).x) + ((*a).y * (*b).y));
}

float	vec3uv_dot(t_v3_uv *a, t_v3_uv *b)
{
	return (((*a).x * (*b).x) + ((*a).y * (*b).y) + ((*a).z * (*b).z));
}

float	vec3_dot(t_v3 *a, t_v3 *b)
{
	return (((*a).x * (*b).x) + ((*a).y * (*b).y) + ((*a).z * (*b).z));
}
