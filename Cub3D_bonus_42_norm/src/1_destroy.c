/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_destroy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:59:37 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 17:02:40 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	destroy_spinlock(t_scene *scene)
{
	pthread_spin_destroy((*scene).fast_lock);
}

void	kill_all_threads(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < THREAD_NUM)
		pthread_kill(*((*scene).thread + i), SIGINT);
}

static void	destroy_upng(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < 6)
		if (*((*scene).upng + i))
			upng_free(*((*scene).upng + i));
}

void	destroy(SDL_Window *window, SDL_Renderer *renderer, t_scene *scene,
SDL_Texture *color_buffer_texture)
{
	SDL_DestroyTexture(color_buffer_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	if (scene)
	{
		if ((*scene).z_buffer)
			free((*scene).z_buffer);
		if ((*scene).color_buffer)
			free((*scene).color_buffer);
		if ((*scene).cloud)
			free((*scene).cloud);
		if ((*scene).triangle_index)
			free((*scene).triangle_index);
		destroy_upng(scene);
		destroy_spinlock(scene);
	}
}
