#include <SDL2/SDL.h>
#include "header.h"

int	set_nothing(int key)
{	
	(void)key;
	return (0);
}

int	set_quit(int key)
{
	(void)key;
	return (1);
}

int	set_index(int key)
{
	return (
		(key == SDLK_ESCAPE)
		+ ((key == SDLK_o) << 1)
		//+ ((key == SDLK_p) << 2)
	);
}
