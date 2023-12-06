/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:23:08 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 00:24:52 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	launch_threads(pthread_t *thread, void *arg)
{
	int	i;

	i = -1;
	while (++i < THREAD_NUM)
		pthread_create(thread + i, NULL, &start, arg);
}

static void	init_spinlock(t_scene *scene, t_pixel_info *pixel_info)
{
	static pthread_spinlock_t	fast_lock;

	pthread_spin_init(&fast_lock, PTHREAD_PROCESS_PRIVATE);
	(*scene).fast_lock = &fast_lock;
	(*pixel_info).fast_lock = &fast_lock;
}

void	init_threads(t_scene *scene)
{
	static t_arg	arg;

	(*scene).arg = (void *)(&arg);
	arg.pixel_info.scene = scene;
	arg.pixel_info.screen_space_origin.x = MIDLE_X;
	arg.pixel_info.screen_space_origin.y = MIDLE_Y;
	arg.pixel_info.screen_space_origin.z = -80;
	arg.pixel_info.rdy = 0;
	arg.pixel_info.call = 0;
	arg.pixel_info.finish = 0;
	init_spinlock(scene, &(arg.pixel_info));
	launch_threads((*scene).thread, (*scene).arg);
}
