#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

char	initialize_window(void)
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		return (write(2, "Error init SDL\n", 15));
//Create Window
	window = SDL_CreateWindow(
				NULL, //borderless
				SDL_WINDOWPOS_CENTERED, //posx
				SDL_WINDOWPOS_CENTERED,//posy
				WIDTH,
				HEIGHT,
				SDL_WINDOW_BORDERLESS,
	);
	if (window == NULL)	
		return (write(2, "Error SDL Window\n", 17));
//Create a renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
		return (write(2, "Error SDL Renderer\n", 19));
	return (0);
}

int	main (void)
{
	if (initialize_window() != 0)
		return (1);
	
	return (0);
}
