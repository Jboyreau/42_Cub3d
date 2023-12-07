/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_draw_filled_triangle2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:13:44 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 21:21:15 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_v3	barycentric_weight(t_pixel_info *pixel_info)
{
	t_v3	weight;
	t_br	ref;

	ref.ap = vec2_subtract(&(*pixel_info).p, &(*pixel_info).a);
	ref.pc = vec2_subtract(&(*pixel_info).c, &(*pixel_info).p);
	ref.pb = vec2_subtract(&(*pixel_info).b, &(*pixel_info).p);
	weight.x = (ref.pc.x * ref.pb.y - ref.pc.y * ref.pb.x)
		* (*pixel_info).para_abc;
	weight.y = ((*pixel_info).ac.x * ref.ap.y - (*pixel_info).ac.y * ref.ap.x)
		* (*pixel_info).para_abc;
	weight.z = 1 - weight.x - weight.y;
	return (weight);
}

void	interpolated_uv_init(t_pixel_info *pixel_info)
{
	(*pixel_info).ac = vec2_subtract(&(*pixel_info).c, &(*pixel_info).a);
	(*pixel_info).ab = vec2_subtract(&(*pixel_info).b, &(*pixel_info).a);
	(*pixel_info).para_abc = 1 / (((*pixel_info).ac.x * (*pixel_info).ab.y)
			- ((*pixel_info).ac.y * (*pixel_info).ab.x));
	(*pixel_info).p0_itu = (*pixel_info).p0.uv.u * (*pixel_info).p0.inv_z;
	(*pixel_info).p1_itu = (*pixel_info).p1.uv.u * (*pixel_info).p1.inv_z;
	(*pixel_info).p2_itu = (*pixel_info).p2.uv.u * (*pixel_info).p2.inv_z;
	(*pixel_info).p0_itv = (*pixel_info).p0.uv.v * (*pixel_info).p0.inv_z;
	(*pixel_info).p1_itv = (*pixel_info).p1.uv.v * (*pixel_info).p1.inv_z;
	(*pixel_info).p2_itv = (*pixel_info).p2.uv.v * (*pixel_info).p2.inv_z;
}

void	draw_line(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{
	(*pixel_info).p.y = (*pixel_info).y;
	while (x_start <= x_end && x_start >= 0 && x_start <= WIDTH)
	{
		(*pixel_info).cell = x_start + y;
		(*pixel_info).p.x = x_start;
		(*pixel_info).weight = barycentric_weight(pixel_info);
		(*pixel_info).interpolated.w = 1 / ((*pixel_info).weight.x
				* (*pixel_info).p0.inv_z + (*pixel_info).weight.y
				* (*pixel_info).p1.inv_z + (*pixel_info).weight.z
				* (*pixel_info).p2.inv_z);
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			(*((*(*pixel_info).scene).z_buffer
				+ (*pixel_info).cell) > (*pixel_info).interpolated.w
			&& ((*pixel_info).weight.x >= 0 && (*pixel_info).weight.y >= 0
			&& (*pixel_info).weight.z >= 0
			&& ((*pixel_info).weight.x + (*pixel_info).weight.y
				+ (*pixel_info).weight.z <= 1)))
			<< ((*pixel_info).interpolated.w < 110)
		](pixel_info);
		++x_start;
	}
}

void	draw_line2(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{
	(*pixel_info).p.y = (*pixel_info).y;
	while (x_end <= x_start && x_end >= 0 && x_end <= WIDTH)
	{
		(*pixel_info).cell = x_end + y;
		(*pixel_info).p.x = x_end;
		(*pixel_info).weight = barycentric_weight(pixel_info);
		(*pixel_info).interpolated.w = 1 / ((*pixel_info).weight.x
				* (*pixel_info).p0.inv_z + (*pixel_info).weight.y
				* (*pixel_info).p1.inv_z + (*pixel_info).weight.z
				* (*pixel_info).p2.inv_z);
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			(*((*(*pixel_info).scene).z_buffer
				+ (*pixel_info).cell) > (*pixel_info).interpolated.w
			&& ((*pixel_info).weight.x >= 0 && (*pixel_info).weight.y >= 0
			&& (*pixel_info).weight.z >= 0
			&& ((*pixel_info).weight.x + (*pixel_info).weight.y
				+ (*pixel_info).weight.z <= 1)))
			<< ((*pixel_info).interpolated.w < 110)
		](pixel_info);
		++x_end;
	}
}
