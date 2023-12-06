/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_check2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:47:08 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 22:48:08 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_uright(t_scene *scene, int px, int pz)
{
	if (check_lim(scene, px, pz))
		return (0);
	if ((*((*scene).map + pz * (*scene).line_len + px) == '?'
			|| *((*scene).map + pz * (*scene).line_len + px) == '1'
			|| *((*scene).map + pz * (*scene).line_len + px) == '_'))
		return (0);
	return (1);
}

int	check_uleft(t_scene *scene, int px, int pz)
{
	if (check_lim(scene, px, pz))
		return (0);
	if ((*((*scene).map + pz * (*scene).line_len + px) == '?'
			|| *((*scene).map + pz * (*scene).line_len + px) == '1'
			|| *((*scene).map + pz * (*scene).line_len + px) == '_'))
		return (0);
	return (1);
}

int	check_dright(t_scene *scene, int px, int pz)
{
	if (check_lim(scene, px, pz))
		return (0);
	if ((*((*scene).map + pz * (*scene).line_len + px) == '?'
			|| *((*scene).map + pz * (*scene).line_len + px) == '1'
			|| *((*scene).map + pz * (*scene).line_len + px) == '_'))
		return (0);
	return (1);
}

int	check_dleft(t_scene *scene, int px, int pz)
{
	if (check_lim(scene, px, pz))
		return (0);
	if ((*((*scene).map + pz * (*scene).line_len + px) == '?'
			|| *((*scene).map + pz * (*scene).line_len + px) == '1'
			|| *((*scene).map + pz * (*scene).line_len + px) == '_'))
		return (0);
	return (1);
}
