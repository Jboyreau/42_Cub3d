#include "header.h"

static void code_mutex_destroyer(pthread_mutex_t *code_mutex)
{
	int i;

	i = -1;
	while (++i < MUTEX_NUM)
		pthread_mutex_destroy(code_mutex + i);
}

static void mutex_buffer_destroyer(pthread_mutex_t *mutex_buffer)
{
	int i;

	i = -1;
	while (++i < BUFF_SIZE)
		pthread_mutex_destroy(mutex_buffer + i);
}

static void	destroy(SDL_Window *window, SDL_Renderer *renderer, t_scene *scene, SDL_Texture *color_buffer_texture)
{
	SDL_DestroyTexture(color_buffer_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	if (scene)
	{
		if ((*scene).z_buffer)
			free((*scene).z_buffer);
		if ((*scene).color_buffer)
			free((*scene).color_buffer);
		if ((*scene).cloud)
			free((*scene).cloud);
		if ((*scene).triangle_index)
			free((*scene).triangle_index);
		if ((*scene).upng)
			upng_free((*scene).upng);
		mutex_buffer_destroyer((*scene).mutex_buffer);
		code_mutex_destroyer((*scene).code_mutex);
		int i = -1;
		while (++i < THREAD_NUM)
			pthread_kill(*((*scene).thread + i), SIGINT);
		pthread_barrier_destroy((*scene).wait_triangle);
		pthread_barrier_destroy((*scene).wait_main_lock);
		pthread_barrier_destroy((*scene).first_wall);
	}
}

static char	initialize_window(SDL_Window **window, SDL_Renderer **renderer, int **color_buffer, SDL_Texture **color_buffer_texture)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (SDL_Quit(), write(2, "Error init SDL\n", 15));
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
		return (SDL_DestroyWindow(*window), SDL_Quit(), write(2, "Error SDL Renderer\n", 19));
//Color_buffer allocation
	*color_buffer = malloc(sizeof(int) * BUFF_SIZE);
	if (*color_buffer == NULL)
		return (SDL_DestroyWindow(*window), SDL_DestroyRenderer(*renderer), SDL_Quit(), 1);
//Create an SDL texture
	*color_buffer_texture = SDL_CreateTexture(
		*renderer,
		SDL_PIXELFORMAT_RGBA32,
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

//Setup
	if (initialize_window(&(canvas.window), &(canvas.renderer), &(canvas.color_buffer), &(canvas.color_buffer_texture)) != 0)
		return (1);
	initialize_fun(&fun);
	scene = initialize_scene(canvas.color_buffer, &fun);
	if (scene == NULL)
		return (write(2, "Scene failed.\n", 14), destroy(canvas.window, canvas.renderer, scene, canvas.color_buffer_texture), 1);
	if (init_threads(scene) == NULL)	
		return (write(2, "Thread failed.\n", 15), destroy(canvas.window, canvas.renderer, scene, canvas.color_buffer_texture), 1);
	clear_color_buffer((long long int *)canvas.color_buffer, (*scene).z_buffer);
//game_loop
	(*scene).previous_frame_time = SDL_GetTicks();
	(*scene).time_to_wait = -1;
	rotation_x(scene, 3.141592);
	perspective_project(scene);
	while (display(&canvas, (*scene).ret))
	{
		(*scene).ret = fun.fun_update[process_input(fun.fun_event, scene)](scene);
		SDL_FlushEvent(SDL_KEYDOWN);
		//SDL_FlushEvent(SDL_KEYUP);
		//(*scene).time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - (*scene).previous_frame_time);
		//(*(*scene).fun).fun_delay[((*scene).time_to_wait > 0)]((*scene).time_to_wait);
		//(*scene).previous_frame_time = SDL_GetTicks();
	}
	unlock_code_mutex((*scene).code_mutex, THREAD_NUM);
	return (destroy(canvas.window, canvas.renderer, scene, canvas.color_buffer_texture), 0);
}
