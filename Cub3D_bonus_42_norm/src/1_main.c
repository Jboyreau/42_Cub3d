/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:39:53 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 16:59:15 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	initialize_window(SDL_Window **window, SDL_Renderer **renderer,
SDL_Texture **color_buffer_texture)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (SDL_Quit(), write(2, "Error init SDL\n", 15));
	*window = SDL_CreateWindow(
			"Cub3D",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_SHOWN
			);
	if (*window == NULL)
		return (write(2, "Error SDL Window\n", 17));
	*renderer = SDL_CreateRenderer(*window, -1, 0);
	if (*renderer == NULL)
		return (SDL_DestroyWindow(*window), SDL_Quit(),
			write(2, "Error SDL Renderer\n", 19));
	*color_buffer_texture = SDL_CreateTexture(
			*renderer,
			SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			WIDTH,
			HEIGHT
			);
	return (0);
}

static void	init_position(t_scene *scene)
{
	int	i;

	rotation_x(scene, 3.141592);
	i = -1;
	while (++i < (*scene).cloud_size)
	{
		(*((*scene).cloud + i)).x += -(*scene).px;
		(*((*scene).cloud + i)).z += (*scene).pz;
	}
	if ((*scene).card == 'S')
		rotation_y(scene, 3.141592);
	if ((*scene).card == 'E')
		rotation_y(scene, 1.5708);
	if ((*scene).card == 'W')
		rotation_y(scene, -1.5708);
}

int	check_map_ext(char **argv)
{
	int		len;
	int		j;
	int		i;
	int		k;
	char	*ext;

	ext = ".cub";
	i = 0;
	while (*(*(argv + 1) + i))
		++i;
	len = i;
	if (len < 5)
		return (1);
	j = 5;
	k = 0;
	while (--j > -1)
	{
		if (*(ext + j) != *(*(argv + 1) + i - k))
			return (1);
		++k;
	}
	return (0);
}

static void	game_loop(t_scene *scene, t_w *canvas, t_f *fun)
{
	while ((*scene).input != 3)
	{
		(*scene).input = process_input((*fun).fun_event, scene);
		(*fun).fun_update[(*scene).input * ((*scene).input != 3)](scene);
		SDL_FlushEvent(SDL_KEYDOWN);
		display(canvas, scene);
	}
}

int	main(int argc, char **argv)
{
	static t_w	canvas = {.window = NULL, .renderer = NULL,
		.color_buffer_texture = NULL};
	t_scene		*scene;
	t_f			fun;

	if (argc < 2 || check_map_ext(argv))
		return (write(2, "Error\nMissing .cub map descriptor.\n", 35), 1);
	initialize_fun(&fun);
	scene = initialize_scene(&fun, *(argv + 1));
	if (scene == NULL)
		return (write(2, "Scene failed.\n", 14), 1);
	if (initialize_window(&(canvas.window), &(canvas.renderer),
			&(canvas.color_buffer_texture)) != 0)
		return (1);
	(init_threads(scene), init_position(scene));
	clear_color_buffer((long long int *)(*scene).color_buffer,
		(*scene).z_buffer);
	perspective_project(scene);
	game_loop(scene, &canvas, &fun);
	kill_all_threads(scene);
	destroy(canvas.window, canvas.renderer, scene, canvas.color_buffer_texture);
	return (0);
}
