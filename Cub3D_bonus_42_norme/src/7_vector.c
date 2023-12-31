/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:50:38 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:58:21 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float	vec2_length(t_v2 *vector)
{
	return (sqrt((*vector).x * (*vector).x + (*vector).y * (*vector).y));
}

float	vec3_length(t_v3 *vector)
{
	return (sqrt((*vector).x * (*vector).x + (*vector).y * (*vector).y
			+ (*vector).z * (*vector).z));
}

t_v2	vec2_subtract(t_v2 *v0, t_v2 *v1)
{
	t_v2	sum;

	sum.x = (*v0).x - (*v1).x;
	sum.y = (*v0).y - (*v1).y;
	return (sum);
}

t_v3_uv	vec3uv_multiplication(t_v3_uv *v0, float factor)
{
	t_v3_uv	new;

	new.x = (*v0).x * factor;
	new.y = (*v0).y * factor;
	new.z = (*v0).z * factor;
	return (new);
}
