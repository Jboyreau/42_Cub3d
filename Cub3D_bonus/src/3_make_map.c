#include "header.h"
static void	destroy_wfr(t_scene *scene, char *map_raw)
{
	if ((*scene).cloud_wall)
		free((*scene).cloud_wall);
	if ((*scene).triangle_index_wall)
		free((*scene).triangle_index_wall);
	if ((*scene).cloud_floor)
		free((*scene).cloud_floor);
	if ((*scene).triangle_index_floor)
		free((*scene).triangle_index_floor);
	if ((*scene).cloud_roof)
		free((*scene).cloud_roof);
	if ((*scene).triangle_index_roof)
		free((*scene).triangle_index_roof);
	if ((*scene).map)
		free((*scene).map);
	if (map_raw)
		free(map_raw);
}

static char *load_map(char *file, int fd, int len, char *buffer)
{
	struct stat info_fichier;

	if (stat(file, &info_fichier) != 0)
	{
		perror("Error get file informations");
		return (NULL);
	}
	if (S_ISDIR(info_fichier.st_mode))
	{
		perror("FILE is a directory");
		return (NULL);
	}
	fd = open(file, O_RDWR);
	if (fd == -1)
		return (NULL);
	len = lseek(fd, 0, SEEK_END) + 1;
	if (len == 1)
		return (NULL);
	buffer = malloc(len);
	if (buffer == NULL)
		return (NULL);
	(lseek(fd, 0, SEEK_SET), read(fd, buffer, len - 1));
	*(buffer + len - 1) = '\0';
	return (close(fd), buffer);
}

static void set_map_size(char *map_raw, int *line_len, int *line_nb)
{
	int	i;
	int len;

	len = 0;
	i = 0;
	while (*(map_raw + i))
	{
		++len;
		if (*(map_raw + i) == '\n')
		{
			++(*line_nb);
			if (len > *line_len)
				*line_len = len;
			len = 0; 
		}
		++i;
	}
}

static void	process_map(char *map_raw, int line_len, int line_nb, int len)
{
	static int		i = -1;
	static int		j = 0;

	(*scene).map = malloc(line_len * line_nb);
	if ((*scene).map == NULL)
		return (NULL);
	while (*(map_raw + (++i)))
	{
		++len;
		if (*(map_raw + i) == '\n')
		{
			while ((len++) <= line_len)
				*((*scene).map + (j++)) = '?';
			len = 0;
		}
		else
		{
			if (*(map_raw + i) == ' ')
				*((*scene).map + (j++)) = '?';
			else
				*((*scene).map + (j++)) = *(map_raw + i);
		}
	}
}

static int	allocate_model(t_scene *scene, int i, int n_wall)
{
	int	map_size;

	map_size = (*scene).line_len * (*scene).line_nb;
	while (++i < map_size)
		if (*((*scene).map + i) == '1')
			++n_wall;
	(*scene).cloud_size = n_wall * (*scene).cloud_size_wall 
	+ map_size * (*scene).cloud_size_floor
	+ map_size * (*scene).cloud_size_roof;
	(*scene).cloud = malloc((*scene).cloud_size * sizeof(t_v3));
	if ((*scene).cloud == NULL)
		return (0);
	(*scene).triangle_index_size = n_wall * (*scene).triangle_index_size_wall
	+ map_size * (*scene).triangle_index_size_floor
	+ map_size * (*scene).triangle_index_size_roof;
	(*scene).triangle_index = malloc((*scene).triangle_index_size * sizeof(t_tri));
	if ((*scene).triangle_index == NULL)
		return (0);
}

static int	assemble_wall(t_scene *scene)
{
	
}

static int	assemble_floor(t_scene *scene)
{
	
}

static int	assemble_roof(t_scene *scene)
{
	
}

int	assemble_map(t_scene *scene)
{
	char	*map_raw;

	(*scene).line_len = 0;
	(*scene).line_nb = 0;
	map_raw = load_map(MAP_PATH, 0, 0, NULL);
	if (map_raw == NULL)
		return (write(2, "Error open map failed.\n", 23), 0);
	set_map_size(map_raw, &((*scene).line_len), &((*scene).line_nb));
	process_map(map_raw, (*scene).line_len, (*scene).line_nb, 0);
	if ((*scene).map == NULL)
		return (write(2, "Error process map failed.\n", 27), 1);
	if (allocate_model(scene, -1, 0) == NULL)
		return (NULL);
	assemble_wall(scene);
	assemble_floor(scene);
	assemble_roof(scene);
	destroy_wfr(scene, map_raw);
	return (1);
}
