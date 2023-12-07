/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_draw_filled_triangle3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:22:19 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 21:29:48 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	flat_bottom_top(t_pixel_info *pixel_info, t_point *p0,
t_point *p1, t_point *p2)
{	
	(*pixel_info).inv_sloap_2 = (((*p0).x - (*p2).x)
			/ (float)((*p0).y - (*p2).y));
	(*pixel_info).inv_sloap_2_factor = THREAD_NUM * (*pixel_info).inv_sloap_2;
	(*pixel_info).y_start = (*p0).y + (*pixel_info).thread_index;
	fill_flat_bottom(pixel_info, p0, p1, (*pixel_info).thread_index);
	(*pixel_info).y_start = (*p2).y - (*pixel_info).thread_index;
	fill_flat_top(pixel_info, p2, p1, (*pixel_info).thread_index);
}

void	flat_top(t_pixel_info *pixel_info,
t_point *p0, t_point *p1, t_point *p2)
{
	(*pixel_info).inv_sloap_2 = (((*p0).x - (*p2).x)
			/ (float)((*p0).y - (*p2).y));
	(*pixel_info).inv_sloap_2_factor = THREAD_NUM * (*pixel_info).inv_sloap_2;
	(*pixel_info).y_start = (*p2).y - (*pixel_info).thread_index;
	fill_flat_top(pixel_info, p2, p1, (*pixel_info).thread_index);
}

void	flat_bottom(t_pixel_info *pixel_info,
t_point *p0, t_point *p1, t_point *p2)
{
	(*pixel_info).inv_sloap_2 = (((*p0).x - (*p2).x)
			/ (float)((*p0).y - (*p2).y));
	(*pixel_info).inv_sloap_2_factor = THREAD_NUM * (*pixel_info).inv_sloap_2;
	(*pixel_info).y_start = (*p0).y + (*pixel_info).thread_index;
	fill_flat_bottom(pixel_info, p0, p1, (*pixel_info).thread_index);
}

void	nothing_tb(t_pixel_info *pixel_info, t_point *p0,
t_point *p1, t_point *p2)
{
	(void)pixel_info;
	(void)p0;
	(void)p1;
	(void)p2;
}
