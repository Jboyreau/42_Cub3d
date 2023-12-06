/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_assemble2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:24:00 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:33:51 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	paste_wall(t_scene *scene, int z, int x, int n)
{
	int	i;
	int	cstart;
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
		*((*scene).triangle_index + tstart
				+ i) = *((*scene).triangle_index_wall + i);
		(*((*scene).triangle_index + tstart
					+ i)).a += n * (*scene).cloud_size_wall;
		(*((*scene).triangle_index + tstart
					+ i)).b += n * (*scene).cloud_size_wall;
		(*((*scene).triangle_index + tstart
					+ i)).c += n * (*scene).cloud_size_wall;
	}
}

void	paste_floor(t_scene *scene, int z, int x, int n)
{
	int	i;
	int	cstart;
	int	tstart;

	tstart = (*scene).nwt + n * (*scene).triangle_index_size_floor;
	cstart = (*scene).nwc + n * (*scene).cloud_size_floor;
	i = -1;
	while (++i < (*scene).cloud_size_floor)
	{
		*((*scene).cloud + cstart + i) = *((*scene).cloud_floor + i);
		(*((*scene).cloud + cstart + i)).x += x * MODEL_SCALE;
		(*((*scene).cloud + cstart + i)).z += z * MODEL_SCALE;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size_floor)
	{
		*((*scene).triangle_index + tstart
				+ i) = *((*scene).triangle_index_floor + i);
		(*((*scene).triangle_index + tstart
					+ i)).a += (*scene).nwc + n * (*scene).cloud_size_floor;
		(*((*scene).triangle_index + tstart
					+ i)).b += (*scene).nwc + n * (*scene).cloud_size_floor;
		(*((*scene).triangle_index + tstart
					+ i)).c += (*scene).nwc + n * (*scene).cloud_size_floor;
	}
}

void	paste_roof(t_scene *scene, int z, int x, int n)
{
	int	i;
	int	cstart;
	int	tstart;

	tstart = (*scene).nwt + n * (*scene).triangle_index_size_roof;
	cstart = (*scene).nwc + n * (*scene).cloud_size_roof;
	i = -1;
	while (++i < (*scene).cloud_size_roof)
	{
		*((*scene).cloud + cstart + i) = *((*scene).cloud_roof + i);
		(*((*scene).cloud + cstart + i)).x += x * MODEL_SCALE;
		(*((*scene).cloud + cstart + i)).z += z * MODEL_SCALE;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size_roof)
	{
		*((*scene).triangle_index + tstart
				+ i) = *((*scene).triangle_index_roof + i);
		(*((*scene).triangle_index + tstart
					+ i)).a += (*scene).nwc + n * (*scene).cloud_size_roof;
		(*((*scene).triangle_index + tstart
					+ i)).b += (*scene).nwc + n * (*scene).cloud_size_roof;
		(*((*scene).triangle_index + tstart
					+ i)).c += (*scene).nwc + n * (*scene).cloud_size_roof;
	}
}

void	assemble_wall(t_scene *scene, int l, int c)
{
	int	nbre_wall;

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
