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
		+ (((*keys).key == SDLK_p) << 1)
		+ (((*keys).wheel == -1 && (*keys).mouse_wheel_event == SDL_MOUSEWHEEL) << 2)
		+ (((*keys).wheel == 1 && (*keys).mouse_wheel_event == SDL_MOUSEWHEEL) << 3)
		+ (((*keys).key == SDLK_KP_MINUS) << 4)
		+ (((*keys).key == SDLK_KP_PLUS) << 5)
		+ (((*keys).key == SDLK_KP_2) << 6)
		+ (((*keys).key == SDLK_KP_8) << 7)
		+ (((*keys).key == SDLK_KP_4) << 8)
		+ (((*keys).key == SDLK_KP_6) << 9)
		+ (((*keys).key == SDLK_KP_MULTIPLY) << 10)
		+ (((*keys).key == SDLK_KP_DIVIDE) << 11)
	);
}
