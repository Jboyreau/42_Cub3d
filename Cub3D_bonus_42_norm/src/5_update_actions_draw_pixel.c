/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_draw_pixel.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:57:36 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 00:13:27 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	find_color(t_pixel_info *pixel_info)
{
	int	cell;

	(*pixel_info).interpolated.u = ((*pixel_info).weight.x
			* (*pixel_info).p0_itu
			+ (*pixel_info).weight.y * (*pixel_info).p1_itu
			+ (*pixel_info).weight.z * (*pixel_info).p2_itu)
		* (*pixel_info).interpolated.w;
	(*pixel_info).interpolated.v = ((*pixel_info).weight.x
			* (*pixel_info).p0_itv
			+ (*pixel_info).weight.y * (*pixel_info).p1_itv
			+ (*pixel_info).weight.z * (*pixel_info).p2_itv)
		* (*pixel_info).interpolated.w;
	cell = *((*(*pixel_info).scene).tex_w
			+ (*pixel_info).texture) * ((int)((*pixel_info).interpolated.v
				* (*((*(*pixel_info).scene).tex_h + (*pixel_info).texture)))
			+ (*pixel_info).interpolated.u);
	cell *= (cell > 0 && cell < *((*(*pixel_info).scene).t_size
				+ (*pixel_info).texture));
	return (*(*((*(*pixel_info).scene).texture
				+ (*pixel_info).texture) + cell));
}

void	draw_per_tri_shading(t_pixel_info *pixel_info)
{
	int	a;
	int	r;
	int	g;
	int	b;

	(*pixel_info).color = 0xff404040;
	a = 0xFF000000;
	r = ((*pixel_info).color & 0x00FF0000) * (*(*pixel_info).scene).dot;
	g = ((*pixel_info).color & 0x0000FF00) * (*(*pixel_info).scene).dot;
	b = ((*pixel_info).color & 0x000000FF) * (*(*pixel_info).scene).dot;
	*((*(*pixel_info).scene).z_buffer
			+ (*pixel_info).cell) = (*pixel_info).interpolated.w;
	*((*(*pixel_info).scene).color_buffer + (*pixel_info).cell) = a
		| (r & 0x00FF0000)
		| (g & 0x0000FF00)
		| (b & 0x000000FF);
}

void	draw_per_pixel_shading(t_pixel_info *pixel_info)
{
	int	a;
	int	r;
	int	g;
	int	b;

	dot(pixel_info);
	(*pixel_info).color = find_color(pixel_info);
	a = 0xFF000000;
	r = ((*pixel_info).color & 0x00FF0000) * (*pixel_info).dot;
	g = ((*pixel_info).color & 0x0000FF00) * (*pixel_info).dot;
	b = ((*pixel_info).color & 0x000000FF) * (*pixel_info).dot;
	*((*(*pixel_info).scene).z_buffer
			+ (*pixel_info).cell) = (*pixel_info).interpolated.w;
	*((*(*pixel_info).scene).color_buffer + (*pixel_info).cell) = a
		| (r & 0x00FF0000)
		| (g & 0x0000FF00)
		| (b & 0x000000FF);
}

void	do_not_draw_pixel(t_pixel_info *pixel_info)
{
	(void)pixel_info;
}
