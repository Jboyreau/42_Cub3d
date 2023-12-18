/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_draw_filled_triangle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:13:29 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 21:56:14 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_filled_triangle(t_point *p0, t_point *p1, t_point *p2,
t_pixel_info *pixel_info)
{
	(*pixel_info).a.x = (*p0).x;
	(*pixel_info).a.y = (*p0).y;
	(*pixel_info).b.x = (*p1).x;
	(*pixel_info).b.y = (*p1).y;
	(*pixel_info).c.x = (*p2).x;
	(*pixel_info).c.y = (*p2).y;
	(*pixel_info).p0 = (*p0);
	(*pixel_info).p1 = (*p1);
	(*pixel_info).p2 = (*p2);
	interpolated_uv_init(pixel_info);
	(*pixel_info).condition = ((*p1).y == (*p0).y && ((*p1).y != (*p2).y))
		+ (((*p1).y == (*p2).y && ((*p1).y != (*p0).y)) << 1);
	call_thread(pixel_info);
}

void	draw_ft012(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		pixel_info
		);
}

void	draw_ft021(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		pixel_info
		);
}
