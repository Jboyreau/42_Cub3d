/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_flood_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:40:21 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:07:40 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	flood_fill2(t_scene *scene, int px, int pz, int *error)
{
	*((*scene).map + pz * (*scene).line_len + px) = '_';
	if (*error && check_uright(scene, px + 1, pz + 1))
		flood_fill(scene, px + 1, pz + 1);
	else if (check_error(scene, px + 1, pz + 1))
		*error = 0;
	if (*error && check_uleft(scene, px - 1, pz + 1))
		flood_fill(scene, px - 1, pz + 1);
	else if (check_error(scene, px - 1, pz + 1))
		*error = 0;
	if (*error && check_dright(scene, px + 1, pz - 1))
		flood_fill(scene, px + 1, pz - 1);
	else if (check_error(scene, px + 1, pz - 1))
		*error = 0;
	if (*error && check_dleft(scene, px - 1, pz - 1))
		flood_fill(scene, px - 1, pz - 1);
	else if (check_error(scene, px - 1, pz - 1))
		*error = 0;
	return (*error);
}

int	flood_fill(t_scene *scene, int px, int pz)
{
	static int	error = 1;

	*((*scene).map + pz * (*scene).line_len + px) = '_';
	if (error && check_up(scene, px, pz + 1))
		flood_fill(scene, px, pz + 1);
	else if (check_error(scene, px, pz + 1))
		error = 0;
	if (error && check_down(scene, px, pz - 1))
		flood_fill(scene, px, pz - 1);
	else if (check_error(scene, px, pz - 1))
		error = 0;
	if (error && check_right(scene, px + 1, pz))
		flood_fill(scene, px + 1, pz);
	else if (check_error(scene, px + 1, pz))
		error = 0;
	if (error && check_left(scene, px - 1, pz))
		flood_fill(scene, px - 1, pz);
	else if (check_error(scene, px -1, pz))
		error = 0;
	error = flood_fill2(scene, px, pz, &error);
	return (error);
}

int	is_valid(t_scene *scene)
{
	char	sc;
	char	ret;

	if (check_garbage(scene) == 0)
		return (0);
	if (count_player(scene) != 1)
		return (write(2, "Error\nBad player quantity.\n", 27), 0);
	sc = *((*scene).map + (*scene).pz * (*scene).line_len + (*scene).px);
	ret = flood_fill(scene, (*scene).px, (*scene).pz);
	*((*scene).map + (*scene).pz * (*scene).line_len + (*scene).px) = sc;
	return (ret);
}
