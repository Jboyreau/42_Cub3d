#include "header.h"

static char	*load_file(char *file, int *len)
{
	int			fd;
	static char	*buffer;

	fd = open(file, O_RDWR);
	if (fd == -1)
		return (NULL);
	*len = lseek(fd, 0, SEEK_END) + 1;
	if (*len == 1)
		return (NULL);
	buffer = malloc(*len);
	if (buffer == NULL)
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, *len - 1);
	*(buffer + *len - 1) = '\0';
	close(fd);
	return (buffer);
}

static void	make_vt(char *obj, t_tex2 *vt)
{
	int i = 0;
	int j = 0;

	while (*(obj + i))
	{
		if (*(obj + i) == 'v' && *(obj + i + 1) == 't' && *(obj + i + 2) == ' ')
			break ;
		++i;
	}
	while (1)
	{
		if (*(obj + i) == '#')
		{
			while (*(obj + ++i) && *(obj + i) != '\n')
				;
			if (*(obj + i))
				++i;
			else
				break ;
		}
		if (*(obj + i) == 'v' && *(obj + i + 1) == 't' && *(obj + i + 2) == ' ')
		{
			i += 3;
			(*(vt + j)).u = strtof(obj + i, NULL);
			while (*(obj + i) != ' ')
				++i;
			(*(vt + j)).v = 1 - strtof(obj + (++i), NULL);
			while ((*(obj + i) && *(obj + i) != '\n'))
				++i;
			++j;
		}
		if (*(obj + i) == 0)
			break ;
		++i;
	}
}

char	check_material(char *str)
{
	char	*material;
	int		j;

	j = 0;
	material = "usemtl";
	while (j < 6 && *(str + j) == *(material + j))
		++j;
	return (j == 6);
}

static int make_triangle_index(t_tri *triangle_index, char *obj, t_tex2 *vt, int part)
{
	int i = 0;
	int	j = 0;
	int	index;

	make_vt(obj, vt);
	index = part;
	while (*(obj + i))
	{
		if (check_material(obj + i))
			++index;
		if (*(obj + i) == 'f' && *(obj + i + 1) == ' ')
			break ;
		++i;
	}
	while (1)
	{
		if (check_material(obj + i))
			++index;
		if (*(obj + i) == '#')
		{
			while (*(obj + ++i) && *(obj + i) != '\n')
				;
			if (*(obj + i))
				++i;
			else
				break ;
		}
		if (*(obj + i) == 'f' && *(obj + i + 1) == ' ')
		{
			i += 2;
			(*(triangle_index + j)).a  = atoi(obj + i) - 1;
			(*(triangle_index + j)).texture = index + (index == -1);
			while (*(obj + i) != '/')
				++i;
			(*(triangle_index + j)).uv_a = *(vt + atoi(obj + (++i)) - 1);
			while (*(obj + i) != ' ')
				++i;
			(*(triangle_index + j)).b  = atoi(obj + (++i)) - 1;
			while (*(obj + i) != '/')
				++i;
			(*(triangle_index + j)).uv_b = *(vt + atoi(obj + (++i)) - 1);
			while (*(obj + i) != ' ')
				++i;
			(*(triangle_index + j)).c  = atoi(obj + (++i)) - 1;
			while (*(obj + i) != '/')
				++i;
			(*(triangle_index + j)).uv_c = *(vt + atoi(obj + (++i)) - 1);
			while ((*(obj + i) && *(obj + i) != '\n'))
				++i;
			++j;
		}
		if (*(obj + i) == 0)
			break ;
		++i;
	}
	return (j);
}

static int make_cloud(t_v3 *cloud, char *obj)
{
	int i = 0;
	int j = 0;

	while (*(obj + i))
	{
		if (*(obj + i) == '#')
		{
			while (*(obj + ++i) && *(obj + i) != '\n')
				;
			if (*(obj + i))
				++i;
			else
				break ;
		}
		if (*(obj + i) == 'v' && *(obj + i + 1) == ' ')
		{
			i += 2;
			(*(cloud + j)).x = strtof(obj + i, NULL);
			while (*(obj + i) != ' ')
				++i;
			(*(cloud + j)).y = strtof(obj + (++i), NULL);
			while (*(obj + i) != ' ')
				++i;
			(*(cloud + j)).z = strtof(obj + (++i), NULL);
			while ((*(obj + i) && *(obj + i) != '\n'))
				++i;
			++j;
		}
		if (*(obj + i) == 0)
			break ;
		++i;
	}
	return (j);
}

char	populate_3d_space(t_scene *scene)
{
	t_tex2			*vt;
	static char		*obj_file;
	int				len;

	obj_file = load_file((*scene).obj_path, &len);
	if (obj_file == NULL)
		return (0);
	(*scene).cloud_temp = malloc(len * sizeof(t_v3));
	if ((*scene).cloud_temp == NULL)
		return (0);
	(*scene).triangle_index_temp = malloc(len * sizeof(t_tri));
	if ((*scene).triangle_index_temp == NULL)
		return (0);
	vt = malloc(len * sizeof(t_tri));
	if (vt == NULL)
		return (0);
	(*scene).cloud_size_temp = make_cloud((*scene).cloud_temp, obj_file);
	(*scene).triangle_index_size_temp = make_triangle_index((*scene).triangle_index_temp, obj_file, vt, (*scene).part);
	if (vt)
		free(vt);
	if (obj_file)
		free(obj_file);
	return (1);
}
