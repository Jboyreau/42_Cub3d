#include <unistd.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

static void	destroy(SDL_Window *window, SDL_Renderer *renderer, int *color_buffer, SDL_Texture *color_buffer_texture)
{
	SDL_DestroyTexture(color_buffer_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	free(color_buffer);
}

static char	initialize_window(SDL_Window **window, SDL_Renderer **renderer, int **color_buffer, SDL_Texture **color_buffer_texture)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (write(2, "Error init SDL\n", 15));
//Create Window
	*window = SDL_CreateWindow(
				NULL, //borderless
				SDL_WINDOWPOS_CENTERED, //posx
				SDL_WINDOWPOS_CENTERED,//posy
				WIDTH,
				HEIGHT,
				SDL_WINDOW_BORDERLESS
	);
	if (*window == NULL)
		return (write(2, "Error SDL Window\n", 17));
//Create a renderer
	*renderer = SDL_CreateRenderer(*window, -1, 0);
	if (*renderer == NULL)
		return (SDL_DestroyWindow(*window), write(2, "Error SDL Renderer\n", 19));
//Color_buffer allocation
	*color_buffer = malloc(sizeof(int) * BUFF_SIZE);
	if (*color_buffer == NULL)
		return (SDL_DestroyWindow(*window), SDL_DestroyRenderer(*renderer), 1);
//Create an SDL texture
	*color_buffer_texture = SDL_CreateTexture(
		*renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH,
		HEIGHT
	);
	return (0);
}

int			main(void)
{
	static t_w	canvas = {.window = NULL, .renderer = NULL, .color_buffer = NULL, .color_buffer_texture = NULL};
	t_scene		*scene;
	t_f			fun;
	t_v3		cube[9*9*9];

//Setup
	if (initialize_window(&(canvas.window), &(canvas.renderer), &(canvas.color_buffer), &(canvas.color_buffer_texture)) != 0)
		return (1);
	initialize_fun(&fun);
	scene = initialize_scene(cube, canvas.color_buffer, SCALE, &fun);
	//clear_color_buffer(canvas.color_buffer);
	clear_color_buffer((long long int *)canvas.color_buffer);
//game_loop
	while (display(&canvas, fun.fun_update[process_input(fun.fun_event)](scene)))
		;
	return (destroy(canvas.window, canvas.renderer, canvas.color_buffer, canvas.color_buffer_texture), 0);
}
