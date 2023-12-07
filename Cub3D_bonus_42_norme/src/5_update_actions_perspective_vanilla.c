/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_perspective_vanilla.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:26:11 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:46:21 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	rotation_x(t_scene *scene, float angle)
{
	float	y;
	float	z;
	int		i;

	i = 0;
	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(angle) - y * sin(angle);
		(*((*scene).cloud + i)).y = y * cos(angle) + z * sin(angle);
		++i;
	}
}

void	rotation_y(t_scene *scene, float angle)
{
	float	x;
	float	z;
	int		i;

	i = 0;
	while (i < (*scene).cloud_size)
	{
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(angle) + x * sin(angle);
		(*((*scene).cloud + i)).x = x * cos(angle) - z * sin(angle);
		++i;
	}
}
