/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_renderer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:21:10 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 00:22:24 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	display(t_w *canvas, t_scene *scene)
{
	SDL_UpdateTexture(
		(*canvas).color_buffer_texture,
		NULL,
		(*scene).color_buffer,
		(int)(WIDTH * sizeof(int))
		);
	SDL_RenderCopy((*canvas).renderer,
		(*canvas).color_buffer_texture, NULL, NULL);
	SDL_RenderPresent((*canvas).renderer);
}
