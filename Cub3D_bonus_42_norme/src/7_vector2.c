/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_vector2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:54:54 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:55:08 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float	vec3_normalize_r(t_v3 *vec)
{
	float	len;

	len = vec3_length(vec);
	(*vec) = vec3_divizion(vec, len);
	return (len);
}

void	vec3_denormalize(t_v3 *vec, float len)
{
	(*vec) = vec3_multiplication(vec, len);
}

void	vec3_normalize(t_v3 *vec)
{
	(*vec) = vec3_divizion(vec, vec3_length(vec));
}

void	vec2_normalize(t_v2 *vec)
{
	(*vec) = vec2_divizion(vec, vec2_length(vec));
}
