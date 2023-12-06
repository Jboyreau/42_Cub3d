/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_check3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:54:08 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:00:09 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_error(t_scene *scene, int px, int pz)
{
	if (*((*scene).map + pz * (*scene).line_len + px) != '1'
		&& *((*scene).map + pz * (*scene).line_len + px) != '_')
		return (1);
	return (0);
}

int	check_lim(t_scene *scene, int px, int pz)
{
	if (px < 0 || px >= (*scene).line_len)
		return (1);
	if (pz < 0 || pz >= (*scene).line_nb)
		return (1);
	return (0);
}

int	check_garbage(t_scene *scene)
{
	int	l;
	int	c;

	l = -1;
	while (++l < (*scene).line_nb)
	{
		c = -1;
		while (++c < (*scene).line_len)
			if (*((*scene).map + l * (*scene).line_len + c) != 'N'
				&& *((*scene).map + l * (*scene).line_len + c) != 'S'
				&& *((*scene).map + l * (*scene).line_len + c) != 'E'
				&& *((*scene).map + l * (*scene).line_len + c) != 'W'
				&& *((*scene).map + l * (*scene).line_len + c) != '0'
				&& *((*scene).map + l * (*scene).line_len + c) != '1'
				&& *((*scene).map + l * (*scene).line_len + c) != '?')
				return (0);
	}
	return (1);
}

int	count_player(t_scene *scene)
{
	int	l;
	int	c;
	int	nb;

	l = -1;
	nb = 0;
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
				(*scene).px = c;
				(*scene).pz = l;
				(*scene).card = *((*scene).map + l * (*scene).line_len + c);
				++nb;
			}
		}
	}
	return (nb);
}
