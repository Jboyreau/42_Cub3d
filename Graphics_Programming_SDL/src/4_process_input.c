#include <SDL2/SDL.h>
#include <stdio.h>
#include "header.h"

int	process_input(int (*fun_event[])(t_keys *))
{
	SDL_Event	event;
	t_keys		keys;

	SDL_PollEvent(&event);
	keys.key = event.key.keysym.sym;
	keys.wheel = event.wheel.y;
	keys.mouse_wheel_event = SDL_MOUSEWHEEL;
	return (
			fun_event[
				+ (event.type == SDL_QUIT)
				+ ((event.type == SDL_KEYDOWN) << 1)
				+ ((event.type == SDL_MOUSEWHEEL) << 2)
			](&keys)
	);
}
