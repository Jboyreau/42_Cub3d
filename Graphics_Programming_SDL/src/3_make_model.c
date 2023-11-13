#include "header.h"
#define START_BUFFER_SIZE 500

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

static int make_triangle_index(t_tri *triangle_index, char *obj)
{
	int i = 0;
	int	j = 0;

	while (*(obj + i))
	{
		if (*(obj + i) == 'f' && *(obj + i + 1) == ' ')
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
		if (*(obj + i) == 'f' && *(obj + i + 1) == ' ')
		{
			i += 2;
			(*(triangle_index + j)).a  = atoi(obj + i) - 1;
			while (*(obj + i) != ' ')
				++i;
			(*(triangle_index + j)).b  = atoi(obj + (++i)) - 1;
			while (*(obj + i) != ' ')
				++i;
			(*(triangle_index + j)).c  = atoi(obj + (++i)) - 1;
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

static int make_cloud(t_v3 *cloud, t_v3 *cloud_save, char *obj)
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
			(*(cloud + j)).x = -strtof(obj + i, NULL);
			(*(cloud_save + j)).x = (*(cloud + j)).x;
			while (*(obj + i) != ' ')
				++i;
			(*(cloud + j)).y = -strtof(obj + (++i), NULL);
			(*(cloud_save + j)).y = (*(cloud + j)).y;
			while (*(obj + i) != ' ')
				++i;
			(*(cloud + j)).z = strtof(obj + (++i), NULL);
			(*(cloud_save + j)).z = (*(cloud + j)).z;
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
	static char	*obj_file;
	int			len;

	obj_file = load_file(OBJ, &len);
	if (obj_file == NULL)
		return (0);
	(*scene).cloud = malloc(len * sizeof(t_v3));
	if ((*scene).cloud == NULL)
		return (0);
	(*scene).cloud_save = malloc(len * sizeof(t_v3));
	if ((*scene).cloud_save == NULL)
		return (0);
	(*scene).triangle_index = malloc(len * sizeof(t_tri));
	if ((*scene).triangle_index == NULL)
		return (0);
	(*scene).cloud_size = make_cloud((*scene).cloud, (*scene).cloud_save, obj_file);
	(*scene).triangle_index_size = make_triangle_index((*scene).triangle_index, obj_file);
/*	for (int i = 0; i < (*scene).cloud_size; ++i)
		printf("v%d : x = %f, y = %f, z = %f\n", i, (*((*scene).cloud + i)).x, (*((*scene).cloud + i)).y, (*((*scene).cloud + i)).z);
	for (int i = 0; i < (*scene).triangle_index_size; ++i)
		printf("f%d : a = %d, b = %d, c = %d\n", i, (*((*scene).triangle_index + i)).a, (*((*scene).triangle_index + i)).b, (*((*scene).triangle_index + i)).c);*/
	(*scene).projected_triangle = malloc(10 * sizeof(t_ptri));
	if ((*scene).projected_triangle == NULL)
		return (0);
	if (obj_file)
		free(obj_file);
	return (1);
}
