#include "header.h"

char	display(t_w *canvas, char status)
{
	SDL_UpdateTexture(
		(*canvas).color_buffer_texture,
		NULL,
		(*canvas).color_buffer,
		(int)(WIDTH * sizeof(int))
	);
	SDL_RenderCopy((*canvas).renderer, (*canvas).color_buffer_texture, NULL, NULL);
	SDL_RenderPresent((*canvas).renderer);
	return (status);
}
