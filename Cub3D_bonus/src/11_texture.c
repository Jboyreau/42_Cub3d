#include "header.h"

char	load_texture(char *file, t_scene *scene, int cardinal)
{
	*((*scene).upng + cardinal) = upng_new_from_file(file);
	if (*((*scene).upng + cardinal) != NULL)
	{
		upng_decode(*((*scene).upng + cardinal));
		if (upng_get_error(*((*scene).upng + cardinal)) == UPNG_EOK)
		{
			*((*scene).texture + cardinal) = (int *)upng_get_buffer(*((*scene).upng + cardinal));
			*((*scene).tex_h + cardinal) = upng_get_height(*((*scene).upng + cardinal));
			*((*scene).tex_w + cardinal) = upng_get_width(*((*scene).upng + cardinal));
			*((*scene).t_size + cardinal) = *((*scene).tex_h + cardinal) * (*((*scene).tex_w + cardinal));
			return (1);
		}
		return (write(2,"Error\nUnable to load texture.\n", 30), 0);
	}
	return (write(2,"Error\nUnable to load texture.\n", 30), 0);
}
