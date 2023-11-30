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

static void	process_map(t_scene *scene, char *map_raw, int line_len, int line_nb)
{
	static int		len = 0;
	static int		i = -1;
	static int		j = 0;

	(*scene).map = malloc(line_len * line_nb);
	if ((*scene).map == NULL)
		return ;
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
	(*scene).cloud = malloc((*scene).cloud_size * 100 * sizeof(t_v3));
	if ((*scene).cloud == NULL)
		return (0);
	(*scene).triangle_index_size = n_wall * (*scene).triangle_index_size_wall
	+ map_size * (*scene).triangle_index_size_floor
	+ map_size * (*scene).triangle_index_size_roof;
	(*scene).triangle_index = malloc((*scene).triangle_index_size * 100 * sizeof(t_tri));
	if ((*scene).triangle_index == NULL)
		return (0);
	return (1);
}

void	paste_wall(t_scene *scene, int z, int x, int n)
{
	int i;

	i = -1;
	while (++i < (*scene).cloud_size_wall)
	{
		*((*scene).cloud + n * (*scene).cloud_size_wall + i) = 
		*((*scene).cloud_wall + i);
		(*((*scene).cloud + n * (*scene).cloud_size_wall + i)).x += x * 4;
		(*((*scene).cloud + n * (*scene).cloud_size_wall + i)).z += z * 4;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size_wall)
	{	
		*((*scene).triangle_index + n * (*scene).triangle_index_size_wall + i) = 
		*((*scene).triangle_index_wall + i);
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_wall + i)).a += 
		n * (*scene).cloud_size_wall;
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_wall + i)).b +=
		n * (*scene).cloud_size_wall;
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_wall + i)).c +=
		n * (*scene).cloud_size_wall;
	}
}

void	paste_floor(t_scene *scene, int z, int x, int n)
{
	int i;

	i = -1;
	while (++i < (*scene).cloud_size_floor)
	{
		*((*scene).cloud + n * (*scene).cloud_size_floor + (*scene).nw * (*scene).cloud_size_wall + i) = 
		*((*scene).cloud_floor + i);
		(*((*scene).cloud + n * (*scene).cloud_size_floor + (*scene).nw * (*scene).cloud_size_wall + i)).x += x * 4;
		(*((*scene).cloud + n * (*scene).cloud_size_floor + (*scene).nw * (*scene).cloud_size_wall + i)).z += z * 4;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size_floor)
	{	
		*((*scene).triangle_index + n * (*scene).triangle_index_size_floor + (*scene).nw * (*scene).triangle_index_size_wall + i) = 
		*((*scene).triangle_index_floor + i);
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_floor + (*scene).nw * (*scene).triangle_index_size_wall + i)).a += 
		n * (*scene).cloud_size_floor;
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_floor + (*scene).nw * (*scene).triangle_index_size_wall + i)).b +=
		n * (*scene).cloud_size_floor;
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_floor + (*scene).nw * (*scene).triangle_index_size_wall + i)).c +=
		n * (*scene).cloud_size_floor;
	}
}

void	paste_roof(t_scene *scene, int z, int x, int n)
{
	int i;
	int	map_size;

	map_size = (*scene).line_len * (*scene).line_nb;
	i = -1;
	while (++i < (*scene).cloud_size_roof)
	{
		*((*scene).cloud + n * (*scene).cloud_size_roof + (*scene).nw * (*scene).cloud_size_wall + map_size * (*scene).cloud_size_roof + i) = 
		*((*scene).cloud_roof + i);
		(*((*scene).cloud + n * (*scene).cloud_size_roof + (*scene).nw * (*scene).cloud_size_wall + map_size * (*scene).cloud_size_roof + i)).x += x * 4;
		(*((*scene).cloud + n * (*scene).cloud_size_roof + (*scene).nw * (*scene).cloud_size_wall + map_size * (*scene).cloud_size_roof + i)).z += z * 4;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size_roof)
	{	
		*((*scene).triangle_index + n * (*scene).triangle_index_size_roof + (*scene).nw * (*scene).triangle_index_size_wall + map_size * (*scene).triangle_index_size_floor + i) = 
		*((*scene).triangle_index_roof + i);
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_roof + (*scene).nw * (*scene).triangle_index_size_wall + map_size * (*scene).triangle_index_size_floor + i)).a += 
		n * (*scene).cloud_size_roof;
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_roof + (*scene).nw * (*scene).triangle_index_size_wall + map_size * (*scene).triangle_index_size_floor + i)).b +=
		n * (*scene).cloud_size_roof;
		(*((*scene).triangle_index + n * (*scene).triangle_index_size_roof + (*scene).nw * (*scene).triangle_index_size_wall + map_size * (*scene).triangle_index_size_floor + i)).c +=
		n * (*scene).cloud_size_roof;
	}
	
}

static void	assemble_wall(t_scene *scene, int l, int c)
{
	int nbre_wall;

	nbre_wall = -1;
	while (++l < (*scene).line_nb)
	{
		c = -1;
		while (++c < (*scene).line_len)
			if (*((*scene).map + l * (*scene).line_len + c) == '1')
				paste_wall(scene, -l, c, ++nbre_wall);
	}
	(*scene).nw = nbre_wall;
}

static void	assemble_floor(t_scene *scene, int l, int c)
{
	int nbre_floor;

	nbre_floor = -1;
	while (++l < (*scene).line_nb)
	{
		c = -1;
		while (++c < (*scene).line_len)
			paste_floor(scene, -l, c, ++nbre_floor);
	}
}

static void	assemble_roof(t_scene *scene, int l, int c)
{
	int nbre_roof;

	nbre_roof = -1;
	while (++l < (*scene).line_nb)
	{
		c = -1;
		while (++c < (*scene).line_len)
			paste_roof(scene, -l, c, ++nbre_roof);
	}
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
	process_map(scene, map_raw, (*scene).line_len, (*scene).line_nb);
	if ((*scene).map == NULL)
		return (write(2, "Error process map failed.\n", 27), 1);
	if (allocate_model(scene, -1, 0) == 0)
		return (0);
	assemble_wall(scene, -1, -1);
	assemble_floor(scene, -1, -1);
	assemble_roof(scene, -1, -1);
	destroy_wfr(scene, map_raw);
	return (1);
}
