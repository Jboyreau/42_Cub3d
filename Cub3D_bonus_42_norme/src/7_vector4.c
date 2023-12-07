/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_vector4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:56:16 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:56:55 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_v2	vec2_multiplication(t_v2 *v0, float factor)
{
	t_v2	new;

	new.x = (*v0).x * factor;
	new.y = (*v0).y * factor;
	return (new);
}

t_v3	vec3_multiplication(t_v3 *v0, float factor)
{
	t_v3	new;

	new.x = (*v0).x * factor;
	new.y = (*v0).y * factor;
	new.z = (*v0).z * factor;
	return (new);
}

t_v2	vec2_divizion(t_v2 *v0, float factor)
{
	t_v2	new;

	new.x = (*v0).x / factor;
	new.y = (*v0).y / factor;
	return (new);
}

t_v3	vec3_divizion(t_v3 *v0, float factor)
{
	t_v3	new;

	factor = 1 / factor;
	new.x = (*v0).x * factor;
	new.y = (*v0).y * factor;
	new.z = (*v0).z * factor;
	return (new);
}
