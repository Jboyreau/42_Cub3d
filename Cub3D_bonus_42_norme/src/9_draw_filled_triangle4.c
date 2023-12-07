/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_draw_filled_triangle4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:23:00 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 21:30:55 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fill_flat_bottom(t_pixel_info *pixel_info, t_point *p0,
t_point *p1, int thread_index)
{
	float	inv_sloap_1;
	float	x_start;
	float	x_end;
	int		y;

	inv_sloap_1 = (((*p1).x - (*p0).x) / (float)((*p1).y - (*p0).y));
	x_start = (*p0).x + thread_index * inv_sloap_1;
	x_end = (*p0).x + thread_index * (*pixel_info).inv_sloap_2;
	inv_sloap_1 *= (float)THREAD_NUM;
	y = (*pixel_info).y_start;
	while (y <= (*p1).y && y <= HEIGHT)
	{
		(*pixel_info).y = y;
		if (x_start < x_end)
			draw_line(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end += (*pixel_info).inv_sloap_2_factor;
		y += THREAD_NUM;
	}
}

void	fill_flat_top(t_pixel_info *pixel_info, t_point *p2,
t_point *p1, int thread_index)
{
	float	inv_sloap_1;
	float	x_start;
	float	x_end;
	int		y;

	inv_sloap_1 = (((*p1).x - (*p2).x) / (float)((*p2).y - (*p1).y));
	x_start = (*p2).x + thread_index * inv_sloap_1;
	x_end = (*p2).x - thread_index * (*pixel_info).inv_sloap_2;
	inv_sloap_1 *= (float)THREAD_NUM;
	y = (*pixel_info).y_start;
	while (y >= (*p1).y && y >= 0)
	{
		(*pixel_info).y = y;
		if (x_start < x_end)
			draw_line(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end -= (*pixel_info).inv_sloap_2_factor;
		y -= THREAD_NUM;
	}
}
