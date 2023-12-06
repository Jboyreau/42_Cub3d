/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:43:51 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 22:44:31 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_up(t_scene *scene, int px, int pz)
{
	if (check_lim(scene, px, pz))
		return (0);
	if ((*((*scene).map + pz * (*scene).line_len + px) == '?'
			|| *((*scene).map + pz * (*scene).line_len + px) == '1'
			|| *((*scene).map + pz * (*scene).line_len + px) == '_'))
		return (0);
	return (1);
}

int	check_down(t_scene *scene, int px, int pz)
{
	if (check_lim(scene, px, pz))
		return (0);
	if ((*((*scene).map + pz * (*scene).line_len + px) == '?'
			|| *((*scene).map + pz * (*scene).line_len + px) == '1'
			|| *((*scene).map + pz * (*scene).line_len + px) == '_'))
		return (0);
	return (1);
}

int	check_right(t_scene *scene, int px, int pz)
{
	if (check_lim(scene, px, pz))
		return (0);
	if ((*((*scene).map + pz * (*scene).line_len + px) == '?'
			|| *((*scene).map + pz * (*scene).line_len + px) == '1'
			|| *((*scene).map + pz * (*scene).line_len + px) == '_'))
		return (0);
	return (1);
}

int	check_left(t_scene *scene, int px, int pz)
{
	if (check_lim(scene, px, pz))
		return (0);
	if ((*((*scene).map + pz * (*scene).line_len + px) == '?'
			|| *((*scene).map + pz * (*scene).line_len + px) == '1'
			|| *((*scene).map + pz * (*scene).line_len + px) == '_'))
		return (0);
	return (1);
}
