#include <stdio.h>
#include <SDL2/SDL.h>
#include "header.h"

int	set_nothing(t_keys *keys)
{	
	(void)keys;
	return (0);
}

int	set_quit(t_keys *keys)
{
	(void)keys;
	return (1);
}

int	set_index(t_keys * keys)
{
	return (
		((*keys).key == SDLK_ESCAPE)
		+ (((*keys).key == SDLK_o) << 1)
		+ (((*keys).wheel == -1 && (*keys).mouse_wheel_event == SDL_MOUSEWHEEL) << 2)
		+ (((*keys).wheel == 1 && (*keys).mouse_wheel_event == SDL_MOUSEWHEEL) << 3)
	);
}
