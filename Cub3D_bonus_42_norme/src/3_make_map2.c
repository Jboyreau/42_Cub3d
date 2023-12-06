/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_make_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:29:19 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:32:28 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	d(t_scene *scene, char *map_raw)
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

char	*load_map(char *file, int fd, int len, char *buffer)
{
	struct stat	info_fichier;

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

void	set_map_size(char *map_raw, int *line_len, int *line_nb)
{
	int	i;
	int	len;

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

int	process_map(t_scene *scene, char *map_raw, int line_len,
int line_nb)
{
	static int		len = 0;
	static int		i = -1;
	static int		j = 0;

	(*scene).map = malloc(line_len * line_nb + 1);
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
