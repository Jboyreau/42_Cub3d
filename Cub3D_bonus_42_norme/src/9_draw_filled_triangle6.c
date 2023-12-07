/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_draw_filled_triangle6.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:40:32 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 21:41:00 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*start(void *arg)
{
	int				thread_index;
	t_pixel_info	pixel_info;

	pixel_info = (*(t_arg *)arg).pixel_info;
	find_thread_index((*pixel_info.scene).thread, &thread_index);
	while ((*(*(t_arg *)arg).pixel_info.scene).input != 3)
	{
		wait_call(&(*(t_arg *)arg).pixel_info);
		pixel_info = (*(t_arg *)arg).pixel_info;
		notify_rdy(&(*(t_arg *)arg).pixel_info);
		pixel_info.thread_index = thread_index;
		(*(*pixel_info.scene).fun).flat_top_or_bottom[
		pixel_info.condition
		](&pixel_info, &pixel_info.p0, &pixel_info.p1, &pixel_info.p2);
		notify_finish(&(*(t_arg *)arg).pixel_info);
	}
	return (NULL);
}

void	wait_rdy(t_pixel_info *pixel_info)
{
	while ((*pixel_info).rdy < THREAD_NUM)
		;
	(*pixel_info).call = 0;
}

void	wait_finish(t_pixel_info *pixel_info)
{
	while ((*pixel_info).finish < THREAD_NUM)
		;
}

void	call_thread(t_pixel_info *pixel_info)
{	
	(*pixel_info).rdy = 0;
	(*pixel_info).finish = 0;
	(*pixel_info).call = 1;
	wait_rdy(pixel_info);
	wait_finish(pixel_info);
}
