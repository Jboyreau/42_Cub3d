#include "header.h"

static void	d(t_scene *scene, char *map_raw)
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
		perror("Error\nUnanble to get file informations.");
		return (NULL);
	}
	if (S_ISDIR(info_fichier.st_mode))
		return (perror("Error\nFILE is a directory."), NULL);
	fd = open(file, O_RDWR);
	if (fd == -1)
		return (write(2, "Error\nCan't open map.\n", 22), NULL);
	len = lseek(fd, 0, SEEK_END) + 1;
	if (len == 1)
		return (write(2, "Error\nInvalid map.\n", 19), NULL);
	buffer = malloc(len);
	if (buffer == NULL)
		return (NULL);
	(lseek(fd, 0, SEEK_SET), read(fd, buffer, len - 1));
	*(buffer + len - 1) = '\0';
	return (close(fd), buffer);
}

static int	is_cardinal(char *map_raw, char **cardinal, int *index_c)
{
	int i;

	if (*(map_raw) == 0)
		return (-1);
	i = -1;
	while (++i < 4)
	{
		if (*(map_raw) == **(cardinal + i) && *(map_raw + 1) == *(*(cardinal + i) + 1))
			return (*index_c = i, 1);
	}
	while (i < 6)
	{
		if (*(map_raw) == **(cardinal + i))
			return (*index_c = i, 1);
		++i;
	}
	return (-1);
}

static void	write_tex(char *map_raw, t_scene *scene, int index, int j)
{
	if (index == 0)
		*((*scene).tno + j) = *(map_raw);
	else if (index == 1)
		*((*scene).tso + j) = *(map_raw);
	else if (index == 2)
		*((*scene).tea + j) = *(map_raw);
	else if (index == 3)
		*((*scene).twe + j) = *(map_raw);
	else if (index == 4)
		*((*scene).tf + j) = *(map_raw);
	else if (index == 5)
		*((*scene).tr + j) = *(map_raw);
}

static void	write_tex_end(t_scene *scene, int index, int j)
{
	if (index == 0)
		*((*scene).tno + j) = 0;
	else if (index == 1)
		*((*scene).tso + j) = 0;
	else if (index == 2)
		*((*scene).tea + j) = 0;
	else if (index == 3)
		*((*scene).twe + j) = 0;
	else if (index == 4)
		*((*scene).tf + j) = 0;
	else if (index == 5)
		*((*scene).tr + j) = 0;
}

static int	get_cardinal(t_scene *scene, char **cardinal, char* map_raw, int *sum)
{
	int			index_c;
	int			j;
	static int	i = 0;

	index_c = -1;
	if (is_cardinal(map_raw + i, cardinal, &index_c) == -1)
		return (0);
	*sum += index_c;
	i += 2;
	while (*(map_raw + i) && *(map_raw + i) == ' ')
		++i;
	j = 0;
	while (*(map_raw + i) && *(map_raw + i) != '\n')
	{
		write_tex(map_raw + i, scene, index_c, j);
		++i;
		++j;
	}
	if ((*map_raw + i) == 0)
		return (0);
	write_tex_end(scene, index_c, j);
	return (++i, 1);
}

static void	purge(char *map_raw)
{
	int	i;
	int	j;
	int	nl_num;

	i = 0;
	j = 0;
	nl_num = 0;
	while (*(map_raw + i) && nl_num < 6)
	{
		if (*(map_raw + i) == '\n')
			++nl_num;
		++i;
	}
	while (*(map_raw + i) && *(map_raw + i) == '\n')
		++i;
	while (*(map_raw + i))
	{
		*(map_raw + j) = *(map_raw + i);
		++i;
		++j;
	}
	*(map_raw + (++j)) = 0;
}

static int	get_texture(t_scene *scene, char *map_raw)
{
	static char	*cardinal[6] = {"NO", "SO", "EA", "WE", "F", "C"};
	int			sum;

	sum = 0;
	if (get_cardinal(scene, cardinal, map_raw, &sum) == 0)
		return (0);
	if (get_cardinal(scene, cardinal, map_raw, &sum) == 0)
		return (0);
	if (get_cardinal(scene, cardinal, map_raw, &sum) == 0)
		return (0);
	if (get_cardinal(scene, cardinal, map_raw, &sum) == 0)
		return (0);
	if (get_cardinal(scene, cardinal, map_raw, &sum) == 0)
		return (0);
	if (get_cardinal(scene, cardinal, map_raw, &sum) == 0)
		return (0);
	if (sum != 15)
		return (0);
	purge(map_raw);
	return (1);
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

static int	process_map(t_scene *scene, char *map_raw, int line_len, int line_nb)
{
	static int		len = 0;
	static int		i = -1;
	static int		j = 0;

	(*scene).map = malloc(line_len * line_nb);
	if ((*scene).map == NULL)
		return (0);
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
	return (1);
}

/*static void	is_valid(char *raw_map)
{
	;
}*/

static int	allocate_model(t_scene *scene, int i, int n_wall)
{
	int	map_size;
	int	n_fr;

	map_size = (*scene).line_len * (*scene).line_nb;
	while (++i < map_size)
		if (*((*scene).map + i) == '1')
			++n_wall;
	n_fr = 0;
	i = 0;
	while (++i < map_size)
		if (*((*scene).map + i) != '?')
			++n_fr;
	(*scene).cloud_size = n_wall * (*scene).cloud_size_wall
	+ n_fr * (*scene).cloud_size_floor
	+ n_fr * (*scene).cloud_size_roof;
	(*scene).cloud = malloc((*scene).cloud_size * sizeof(t_v3));
	if ((*scene).cloud == NULL)
		return (0);
	(*scene).triangle_index_size = n_wall * (*scene).triangle_index_size_wall
	+ n_fr * (*scene).triangle_index_size_floor
	+ n_fr * (*scene).triangle_index_size_roof;
	(*scene).triangle_index = malloc((*scene).triangle_index_size * sizeof(t_tri));
	if ((*scene).triangle_index == NULL)
		return (0);
	return (1);
}

void	paste_wall(t_scene *scene, int z, int x, int n)
{
	int i;
	int cstart;
	int	tstart;

	cstart = n * (*scene).cloud_size_wall;
	tstart = n * (*scene).triangle_index_size_wall;
	i = -1;
	while (++i < (*scene).cloud_size_wall)
	{
		*((*scene).cloud + cstart + i) = *((*scene).cloud_wall + i);
		(*((*scene).cloud + cstart + i)).x += x * MODEL_SCALE;
		(*((*scene).cloud + cstart + i)).z += z * MODEL_SCALE;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size_wall)
	{
		*((*scene).triangle_index + tstart + i) = *((*scene).triangle_index_wall + i);
		(*((*scene).triangle_index + tstart + i)).a += n * (*scene).cloud_size_wall;
		(*((*scene).triangle_index + tstart + i)).b += n * (*scene).cloud_size_wall;
		(*((*scene).triangle_index + tstart + i)).c += n * (*scene).cloud_size_wall;
	}
}

void	paste_floor(t_scene *scene, int z, int x, int n)
{
	int i;
	int cstart;
	int	tstart;

	tstart = (*scene).nwt + n * (*scene).triangle_index_size_floor;
	cstart = (*scene).nwc + n * (*scene).cloud_size_floor;
	i = -1;
	while (++i < (*scene).cloud_size_floor)
	{
		*((*scene).cloud + cstart + i) = *((*scene).cloud_floor + i);
		(*((*scene).cloud +  cstart + i)).x += x * MODEL_SCALE;
		(*((*scene).cloud +  cstart + i)).z += z * MODEL_SCALE;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size_floor)
	{	
		*((*scene).triangle_index + tstart + i) = *((*scene).triangle_index_floor + i);
		(*((*scene).triangle_index + tstart + i)).a += (*scene).nwc + n * (*scene).cloud_size_floor;
		(*((*scene).triangle_index + tstart + i)).b += (*scene).nwc + n * (*scene).cloud_size_floor;
		(*((*scene).triangle_index + tstart + i)).c += (*scene).nwc + n * (*scene).cloud_size_floor;
	}
}

void	paste_roof(t_scene *scene, int z, int x, int n)
{
	int i;
	int cstart;
	int	tstart;

	tstart = (*scene).nwt + n * (*scene).triangle_index_size_roof;
	cstart = (*scene).nwc + n * (*scene).cloud_size_roof;
	i = -1;
	while (++i < (*scene).cloud_size_roof)
	{
		*((*scene).cloud + cstart + i) = 
		*((*scene).cloud_roof + i);
		(*((*scene).cloud + cstart + i)).x += x * MODEL_SCALE;
		(*((*scene).cloud + cstart + i)).z += z * MODEL_SCALE;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size_roof)
	{	
		*((*scene).triangle_index + tstart + i) = *((*scene).triangle_index_roof + i);
		(*((*scene).triangle_index + tstart + i)).a += (*scene).nwc + n * (*scene).cloud_size_roof;
		(*((*scene).triangle_index + tstart + i)).b += (*scene).nwc + n * (*scene).cloud_size_roof;
		(*((*scene).triangle_index + tstart + i)).c += (*scene).nwc + n * (*scene).cloud_size_roof;
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
				paste_wall(scene, l, c, ++nbre_wall);
	}
	(*scene).wall_last_index = (nbre_wall + 1) * (*scene).cloud_size_wall;
	(*scene).nwc = (nbre_wall + 1) * (*scene).cloud_size_wall;
	(*scene).nwt = (nbre_wall + 1) * (*scene).triangle_index_size_wall;
}

static void	assemble_floor(t_scene *scene, int l, int c)
{
	int nbre_floor;

	nbre_floor = -1;
	while (++l < (*scene).line_nb)
	{
		c = -1;
		while (++c < (*scene).line_len)
			if (*((*scene).map + l * (*scene).line_len + c) != '?')
				paste_floor(scene, l, c, ++nbre_floor);
	}
	(*scene).nwc += (nbre_floor + 1) * (*scene).cloud_size_floor;
	(*scene).nwt += (nbre_floor + 1) * (*scene).triangle_index_size_floor;
}

static void	assemble_roof(t_scene *scene, int l, int c)
{
	int nbre_roof;

	nbre_roof = -1;
	while (++l < (*scene).line_nb)
	{
		c = -1;
		while (++c < (*scene).line_len)
			if (*((*scene).map + l * (*scene).line_len + c) != '?')
				paste_roof(scene, l, c, ++nbre_roof);
	}
}

static void	get_player_position(t_scene *scene, int l, int c)
{
	while (++l < (*scene).line_nb)
	{
		c = -1;
		while (++c < (*scene).line_len)
			if (*((*scene).map + l * (*scene).line_len + c) == 'N'
			|| *((*scene).map + l * (*scene).line_len + c) == 'S'
			|| *((*scene).map + l * (*scene).line_len + c) == 'E'
			|| *((*scene).map + l * (*scene).line_len + c) == 'W')
			{
				(*scene).px = c * MODEL_SCALE;
				(*scene).pz = l * MODEL_SCALE;
				(*scene).card = *((*scene).map + l * (*scene).line_len + c); 
			}
	}
}

static void	assemble(t_scene *scene)
{
	assemble_wall(scene, -1, -1);
	assemble_floor(scene, -1, -1);
	assemble_roof(scene, -1, -1);
	get_player_position(scene, -1, -1);
}

static void init_stuff(t_scene *scene)
{
	(*scene).map = NULL;
	(*scene).line_len = 0;
	(*scene).line_nb = 0;
}

static void p(char *str, int len)
{
	write(2, str, len);
}

int	assemble_map(t_scene *scene)
{
	static char	*map_raw = NULL;
	static char *e = "Error\n Wrong texture descriptor.\n";

	init_stuff(scene);
	map_raw = load_map(MAP_PATH, 0, 0, NULL);
	if (map_raw == NULL)
		return (d(scene, map_raw), p("Error\n Load map failed.\n", 24), 0);
/***************************************************************************/
	if (get_texture(scene, map_raw) == 0)
		return (d(scene, map_raw), p(e, 33), 0);
	set_map_size(map_raw, &((*scene).line_len), &((*scene).line_nb));
	if (process_map(scene, map_raw, (*scene).line_len, (*scene).line_nb) == 0)
		return (d(scene, map_raw), p("Error\n Process map failed.\n", 28), 0);
	//if (is_valid(map_raw) == 0) //only '0' '1' '?' 'N' 'S' 'E' 'W'; flood fill (pos x;y < 0) ou (pos x;y > lien_len || line nb) ou (pos x;y == '?') => invalid; ligne ???? ou 0????1
	//	return (d(scene, map_raw), p("Error\n Map is invalid.\n", 23), 0);
/***************************************************************************/
	if (allocate_model(scene, -1, 0) == 0)
		return (d(scene, map_raw), 0);
	assemble(scene);
	return (d(scene, map_raw), 1);
}
