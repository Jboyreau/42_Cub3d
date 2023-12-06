/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_make_model.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:05:18 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 20:09:08 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_cloud(t_v3 *cloud, char *obj, int *i, int *j)
{
	(*i) += 2;
	(*(cloud + *j)).x = strtof(obj + *i, NULL);
	while (*(obj + *i) != ' ')
		++(*i);
	(*(cloud + *j)).y = strtof(obj + (++(*i)), NULL);
	while (*(obj + *i) != ' ')
		++(*i);
	(*(cloud + *j)).z = strtof(obj + (++(*i)), NULL);
	while ((*(obj + *i) && *(obj + *i) != '\n'))
		++(*i);
	++(*j);
}

static int	make_cloud(t_v3 *cloud, char *obj)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
			print_cloud(cloud, obj, &i, &j);
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
	(*scene).triangle_index_size_temp = make_triangle_index(
			(*scene).triangle_index_temp, obj_file, vt, (*scene).part);
	if (vt)
		free(vt);
	if (obj_file)
		free(obj_file);
	return (1);
}
