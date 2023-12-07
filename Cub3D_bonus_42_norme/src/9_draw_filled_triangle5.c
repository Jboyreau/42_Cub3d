/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_draw_filled_triangle5.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:34:09 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 21:48:14 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	wait_call(t_pixel_info *pixel_info)
{
	while ((*pixel_info).call < 1)
		;
}

void	notify_rdy(t_pixel_info *pixel_info)
{
	pthread_spin_lock((*pixel_info).fast_lock);
	++(*pixel_info).rdy;
	pthread_spin_unlock((*pixel_info).fast_lock);
	while ((*pixel_info).call)
		;
}

void	notify_finish(t_pixel_info *pixel_info)
{
	pthread_spin_lock((*pixel_info).fast_lock);
	++(*pixel_info).finish;
	pthread_spin_unlock((*pixel_info).fast_lock);
}

void	find_thread_index(pthread_t *thread, int *thread_index)
{
	pthread_t		id;

	*thread_index = 0;
	id = pthread_self();
	pthread_detach(id);
	while (pthread_equal(*(thread + *thread_index), id) == 0)
		++(*thread_index);
}
