/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_process_input_actions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:44:00 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:50:25 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	set_nothing(t_keys *keys)
{
	(void)keys;
	return (0);
}

int	set_quit(t_keys *keys)
{
	(void)keys;
	return (3);
}

int	set_index(t_keys *keys)
{
	return (
		((*keys).key == SDLK_ESCAPE)
		+ ((*keys).key == SDLK_ESCAPE)
		+ ((*keys).key == SDLK_ESCAPE)
		+ (((*keys).wheel == -1 && (*keys).mouse_wheel_event == SDL_MOUSEWHEEL))
		+ (((*keys).wheel == 1
				&& (*keys).mouse_wheel_event == SDL_MOUSEWHEEL) << 1)
		+ (((*keys).key == SDLK_s) << 2)
		+ (((*keys).key == SDLK_z) << 3)
		+ (((*keys).key == SDLK_KP_2) << 4)
		+ (((*keys).key == SDLK_KP_8) << 5)
		+ (((*keys).key == SDLK_KP_4) << 6)
		+ (((*keys).key == SDLK_KP_6) << 7)
		+ (((*keys).key == SDLK_d) << 8)
		+ (((*keys).key == SDLK_q) << 9)
		+ (((*keys).key == SDLK_PAGEDOWN) << 10)
		+ (((*keys).key == SDLK_PAGEUP) << 11)
		+ (((*keys).key == SDLK_DOWN) << 12)
		+ (((*keys).key == SDLK_UP) << 13)
		+ (((*keys).key == SDLK_LEFT) << 14)
		+ (((*keys).key == SDLK_RIGHT) << 15)
	);
}
