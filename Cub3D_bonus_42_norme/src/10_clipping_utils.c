/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_clipping_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:06 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 20:10:27 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	face_uv(t_v3_uv *a, t_tex2 *face)
{
	(*a).u = (*face).u;
	(*a).v = (*face).v;
}

void	uv_tv3(t_v3 *b, t_v3_uv *a)
{
	(*b).x = (*a).x;
	(*b).y = (*a).y;
	(*b).z = (*a).z;
}

void	tv3_uv(t_v3_uv *b, t_v3 *a)
{
	(*b).x = (*a).x;
	(*b).y = (*a).y;
	(*b).z = (*a).z;
}
