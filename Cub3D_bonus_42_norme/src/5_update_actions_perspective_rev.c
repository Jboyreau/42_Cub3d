/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_perspective_rev.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:21:25 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:45:34 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	rev_camera_rotation_x(t_scene *scene, int i, float angle)
{
	float	y;
	float	z;

	y = (*((*scene).cloud + i)).y;
	z = (*((*scene).cloud + i)).z;
	(*((*scene).cloud + i)).z = z * cos(angle) - y * sin(angle);
	(*((*scene).cloud + i)).y = y * cos(angle) + z * sin(angle);
}

void	rev_camera_rotation_origin_x(t_v3 *camera_position, float angle)
{
	float	y;
	float	z;

	y = (*camera_position).y;
	z = (*camera_position).z;
	(*camera_position).z = z * cos(angle) - y * sin(angle);
	(*camera_position).y = y * cos(angle) + z * sin(angle);
}
