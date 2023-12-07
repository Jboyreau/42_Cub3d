/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_fun2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:19:48 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 17:07:50 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//Choose between flat top, flat bottom or both triangle/
void	initialize_flat_top_or_bottom(void (*flat_top_or_bottom[])
(t_pixel_info *info, t_point *p0, t_point *p1, t_point *p2))
{
	flat_top_or_bottom[0] = &flat_bottom_top;
	flat_top_or_bottom[1] = &flat_top;
	flat_top_or_bottom[2] = &flat_bottom;
	flat_top_or_bottom[4] = &nothing_tb;
	flat_top_or_bottom[5] = &nothing_tb;
	flat_top_or_bottom[6] = &nothing_tb;
}

//Fill triangle
void	initialize_draw_ft(void (*draw_ft[])
(t_pixel_info *t_pixel_info, int i))
{
	draw_ft[0] = &draw_ft012;
	draw_ft[1] = &draw_ft021;
	draw_ft[2] = &draw_ft102;
	draw_ft[4] = &draw_ft120;
	draw_ft[8] = &draw_ft201;
	draw_ft[16] = &draw_ft210;
}

//Back face culling or not
void	initialize_culling(void (*culling[])(t_scene *scene, int i,
t_pixel_info *pixel_info))
{
	culling[0] = &triangle_to_nowhere;
	culling[1] = &triangle_to_color_buffer;
}
