#include "header.h"
#define START_BUFFER_SIZE 500

/*
static void make_triangle_index(t_tri *triangle_index)
{
	//front
	(*triangle_index).a = 1; (*triangle_index).b = 2; (*triangle_index).c = 3;
	(*(triangle_index + 1)).a = 1; (*(triangle_index + 1)).b = 3; (*(triangle_index + 1)).c = 4;
	//right
	(*(triangle_index + 2)).a = 4; (*(triangle_index + 2)).b = 3; (*(triangle_index + 2)).c = 5;
	(*(triangle_index + 3)).a = 4; (*(triangle_index + 3)).b = 5; (*(triangle_index + 3)).c = 6;
	//back
	(*(triangle_index + 4)).a = 6; (*(triangle_index + 4)).b = 5; (*(triangle_index + 4)).c = 7;
	(*(triangle_index + 5)).a = 6; (*(triangle_index + 5)).b = 7; (*(triangle_index + 5)).c = 8;
	//left
	(*(triangle_index + 6)).a = 8; (*(triangle_index + 6)).b = 7; (*(triangle_index + 6)).c = 2;
	(*(triangle_index + 7)).a = 8; (*(triangle_index + 7)).b = 2; (*(triangle_index + 7)).c = 1;
	//top
	(*(triangle_index + 8)).a = 2; (*(triangle_index + 8)).b = 7; (*(triangle_index + 8)).c = 5;
	(*(triangle_index + 9)).a = 2; (*(triangle_index + 9)).b = 5; (*(triangle_index + 9)).c = 3;
	//botom
	(*(triangle_index + 10)).a = 6; (*(triangle_index + 10)).b = 8; (*(triangle_index + 10)).c = 1;
	(*(triangle_index + 11)).a = 6; (*(triangle_index + 11)).b = 1; (*(triangle_index + 11)).c = 4;
}

static void make_cloud(t_v3 *cloud)
{
	(*cloud).x = -1; (*cloud).y = -1; (*cloud).z = -1; //1
	(*(cloud + 1)).x = -1; (*(cloud + 1)).y = 1; (*(cloud + 1)).z = -1; //2
	(*(cloud + 2)).x = 1; (*(cloud + 2)).y = 1; (*(cloud + 2)).z = -1; //3
	(*(cloud + 3)).x = 1; (*(cloud + 3)).y = -1; (*(cloud + 3)).z = -1; //4
	(*(cloud + 4)).x = 1; (*(cloud + 4)).y = 1; (*(cloud + 4)).z = 1; //5
	(*(cloud + 5)).x = 1; (*(cloud + 5)).y = -1; (*(cloud + 5)).z = 1; //6
	(*(cloud + 6)).x = -1; (*(cloud + 6)).y = 1; (*(cloud + 6)).z = 1; //7
	(*(cloud + 7)).x = -1; (*(cloud + 7)).y = -1; (*(cloud + 7)).z = 1; //8
}
*/

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
	*(buffer + *len) = '\0';
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
			(*(cloud + j)).x = -strtof(obj + i, NULL);
			while (*(obj + i) != ' ')
				++i;
			(*(cloud + j)).y = -strtof(obj + (++i), NULL);
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
	/*	if (*(obj + i) == 'v' && *(obj + i + 1) == 't')
			break ;*/
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
	(*scene).triangle_index = malloc(len * sizeof(t_tri));
	if ((*scene).triangle_index == NULL)
		return (0);
	(*scene).cloud_size = make_cloud((*scene).cloud, obj_file);
	(*scene).triangle_index_size = make_triangle_index((*scene).triangle_index, obj_file);
/*	for (int i = 0; i < (*scene).cloud_size; ++i)
		printf("v%d : x = %f, y = %f, z = %f\n", i, (*((*scene).cloud + i)).x, (*((*scene).cloud + i)).y, (*((*scene).cloud + i)).z);
	for (int i = 0; i < (*scene).triangle_index_size; ++i)
		printf("f%d : a = %d, b = %d, c = %d\n", i, (*((*scene).triangle_index + i)).a, (*((*scene).triangle_index + i)).b, (*((*scene).triangle_index + i)).c);*/
	(*scene).projected_triangle = malloc((*scene).triangle_index_size * sizeof(t_ptri));
	if ((*scene).triangle_index == NULL)
		return (0);
	if (obj_file)
		free(obj_file);
	return (1);
}
