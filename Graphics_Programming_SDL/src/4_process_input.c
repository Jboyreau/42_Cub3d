#include "header.h"

int	process_input(int (*fun_event[])(t_keys *), t_scene *scene)
{
	SDL_Event		event;
	t_keys			keys;

	(*scene).poll_return = SDL_PollEvent(&event);
	keys.key = event.key.keysym.sym;
	keys.wheel = event.wheel.y;
	keys.mouse_wheel_event = SDL_MOUSEWHEEL;
	return (
			fun_event[
				+ (event.type == SDL_QUIT)
				+ (((event.type == SDL_KEYDOWN) || (event.type == SDL_MOUSEWHEEL)) << 1)
			](&keys)
	);
}
