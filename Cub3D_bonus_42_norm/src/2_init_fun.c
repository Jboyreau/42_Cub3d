/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:13:01 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 20:54:32 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//According to the coordinate value the pixel is displayed or not.
static void	initialize_fun_draw_pixel(void (*fun_draw_pixel[])(t_pixel_info *))
{
	fun_draw_pixel[0] = &do_not_draw_pixel;
	fun_draw_pixel[1] = &draw_per_tri_shading;
	fun_draw_pixel[2] = &draw_per_pixel_shading;
}

//According to the value of the pressed key a function is choosed.
static void	initialize_fun_key_triggered(char (*fun_update[])(t_scene *))
{
	fun_update[0] = &nothing;
	fun_update[1] = &perspective_project_zoom_minus;
	fun_update[2] = &perspective_project_zoom_plus;
	fun_update[4] = &perspective_project_far;
	fun_update[8] = &perspective_project_close;
	fun_update[16] = &rotation_x_minus;
	fun_update[32] = &rotation_x_plus;
	fun_update[64] = &rotation_y_minus;
	fun_update[128] = &rotation_y_plus;
	fun_update[256] = &perspective_project_left;
	fun_update[512] = &perspective_project_right;
	fun_update[1024] = &perspective_project_up;
	fun_update[2048] = &perspective_project_down;
	fun_update[4096] = &camera_rotation_x_minus;
	fun_update[8192] = &camera_rotation_x_plus;
	fun_update[16384] = &camera_rotation_y_minus;
	fun_update[32768] = &camera_rotation_y_plus;
}

//According to the value of the event (press key or not) a function is choosed.
static void	initialize_fun_event(int (*fun_event[])(t_keys *))
{
	fun_event[0] = &set_nothing;
	fun_event[1] = &set_quit;
	fun_event[2] = &set_index;
}

void	initialize_fun(t_f *fun)
{
	initialize_fun_key_triggered((*fun).fun_update);
	initialize_fun_event((*fun).fun_event);
	initialize_fun_draw_pixel((*fun).fun_draw_pixel);
	initialize_culling((*fun).culling);
	initialize_draw_ft((*fun).draw_ft);
	initialize_flat_top_or_bottom((*fun).flat_top_or_bottom);
	initialize_start_draw_ft((*fun).start_draw_ft);
	initialize_inter((*fun).inter);
}
