/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_assemble.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:17:30 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:23:38 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	assemble_floor(t_scene *scene, int l, int c)
{
	int	nbre_floor;

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
	int	nbre_roof;

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
		{
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
}

void	assemble(t_scene *scene)
{
	assemble_wall(scene, -1, -1);
	assemble_floor(scene, -1, -1);
	assemble_roof(scene, -1, -1);
	get_player_position(scene, -1, -1);
}
