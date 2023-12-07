/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_rotation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:58:43 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:47:54 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	rotation_x_minus(t_scene *scene)
{
	float	y;
	float	z;
	int		i;

	i = 0;
	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y - (*scene).camera.position.y;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		(*((*scene).cloud + i)).z = z * cos(R_INC_MINUS) - y * sin(R_INC_MINUS);
		(*((*scene).cloud + i)).y = y * cos(R_INC_MINUS) + z * sin(R_INC_MINUS);
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	rotation_x_plus(t_scene *scene)
{
	float	y;
	float	z;
	int		i;

	i = 0;
	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y - (*scene).camera.position.y;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		(*((*scene).cloud + i)).z = z * cos(R_INC_PLUS) - y * sin(R_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(R_INC_PLUS) + z * sin(R_INC_PLUS);
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	rotation_y_minus(t_scene *scene)
{
	float	x;
	float	z;
	int		i;

	i = 0;
	while (i < (*scene).cloud_size)
	{
		x = (*((*scene).cloud + i)).x - (*scene).camera.position.x;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		(*((*scene).cloud + i)).z = z * cos(R_INC_MINUS) + x * sin(R_INC_MINUS);
		(*((*scene).cloud + i)).x = x * cos(R_INC_MINUS) - z * sin(R_INC_MINUS);
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	rotation_y_plus(t_scene *scene)
{
	float	x;
	float	z;
	int		i;

	i = 0;
	while (i < (*scene).cloud_size)
	{	
		x = (*((*scene).cloud + i)).x - (*scene).camera.position.x;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		(*((*scene).cloud + i)).z = z * cos(R_INC_PLUS) + x * sin(R_INC_PLUS);
		(*((*scene).cloud + i)).x = x * cos(R_INC_PLUS) - z * sin(R_INC_PLUS);
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}
