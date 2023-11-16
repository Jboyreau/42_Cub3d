#include "header.h"

char	load_texture(char *file, t_scene *scene)
{
	(*scene).upng = upng_new_from_file(file);
	if ((*scene).upng != NULL)
	{
		upng_decode((*scene).upng);
		if (upng_get_error((*scene).upng) == UPNG_EOK)
		{
			(*scene).texture = (int *)upng_get_buffer((*scene).upng);
			(*scene).tex_h = upng_get_height((*scene).upng); printf("text_h = %d\n", (*scene).tex_h);
			(*scene).tex_w = upng_get_width((*scene).upng); printf("text_w = %d\n", (*scene).tex_w);
			(*scene).t_size = (*scene).tex_h * (*scene).tex_w;
			return (1);
		}
		return (0);
	}
	return (0);
}
