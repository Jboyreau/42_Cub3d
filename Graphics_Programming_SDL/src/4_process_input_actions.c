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
		+ (((*keys).key == SDLK_s) << 4)
		+ (((*keys).key == SDLK_z) << 5)
		+ (((*keys).key == SDLK_KP_2) << 6)
		+ (((*keys).key == SDLK_KP_8) << 7)
		+ (((*keys).key == SDLK_KP_4) << 8)
		+ (((*keys).key == SDLK_KP_6) << 9)
		+ (((*keys).key == SDLK_KP_MULTIPLY) << 10)
		+ (((*keys).key == SDLK_KP_DIVIDE) << 11)
		+ (((*keys).key == SDLK_d) << 12)
		+ (((*keys).key == SDLK_q) << 13)
		+ (((*keys).key == SDLK_PAGEDOWN) << 14)
		+ (((*keys).key == SDLK_PAGEUP) << 15)
		+ (((*keys).key == SDLK_DOWN) * 26)
		+ (((*keys).key == SDLK_UP) * 27)
		+ (((*keys).key == SDLK_LEFT) * 28)
		+ (((*keys).key == SDLK_RIGHT) * 29)
	);
}
