#include <SDL2/SDL.h>

void	delay(int time_to_wait)
{
	SDL_Delay(time_to_wait);
}

void	do_not_delay(int time_to_wait)
{
	(void) time_to_wait;
}
