/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:13:46 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:19:10 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_cardinal(char *map_raw, char **cardinal, int *index_c)
{
	int	i;

	if (*(map_raw) == 0)
		return (-1);
	i = -1;
	while (++i < 4)
	{
		if (*(map_raw) == **(cardinal + i)
			&& *(map_raw + 1) == *(*(cardinal + i) + 1))
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

static int	get_cardinal(t_scene *scene, char **cardinal, char *map_raw,
int *sum)
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

int	get_texture(t_scene *scene, char *map_raw)
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
