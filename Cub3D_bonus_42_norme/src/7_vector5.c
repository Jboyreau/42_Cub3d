/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_vector5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:57:18 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:57:59 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_v3_uv	vec3uv_subtract(t_v3_uv *v0, t_v3_uv *v1)
{
	t_v3_uv	sum;

	sum.x = (*v0).x - (*v1).x;
	sum.y = (*v0).y - (*v1).y;
	sum.z = (*v0).z - (*v1).z;
	return (sum);
}

t_v3	vec3_subtract(t_v3 *v0, t_v3 *v1)
{
	t_v3	sum;

	sum.x = (*v0).x - (*v1).x;
	sum.y = (*v0).y - (*v1).y;
	sum.z = (*v0).z - (*v1).z;
	return (sum);
}

t_v2	vec2_addition(t_v2 *v0, t_v2 *v1)
{
	t_v2	sum;

	sum.x = (*v0).x + (*v1).x;
	sum.y = (*v0).y + (*v1).y;
	return (sum);
}

t_v3	vec3_addition(t_v3 *v0, t_v3 *v1)
{
	t_v3	sum;

	sum.x = (*v0).x + (*v1).x;
	sum.y = (*v0).y + (*v1).y;
	sum.z = (*v0).z + (*v1).z;
	return (sum);
}
