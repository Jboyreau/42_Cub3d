#include <SDL2/SDL.h>
#include "header.h"

int	process_input(int (*fun_event[])(int))
{
	SDL_Event event;

	SDL_PollEvent(&event);
	return (
			fun_event[
				+ (event.type == SDL_QUIT)
				+ ((event.type == SDL_KEYDOWN) << 1)
			](event.key.keysym.sym)
	);
}
