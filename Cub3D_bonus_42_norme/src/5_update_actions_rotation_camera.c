/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_rotation_camera.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:28:30 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 19:44:17 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	camera_rotation_x_minus(t_scene *scene)
{
	float	y;
	float	z;
	int		i;

	i = 0;
	(*scene).camera.rotation.x += R_INC_MINUS;
	y = (*scene).camera.position.y;
	z = (*scene).camera.position.z;
	(*scene).camera.position.z = (z * cos(R_INC_MINUS) - y * sin(R_INC_MINUS));
	(*scene).camera.position.y = (y * cos(R_INC_MINUS) + z * sin(R_INC_MINUS));
	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(R_INC_MINUS) - y * sin(R_INC_MINUS);
		(*((*scene).cloud + i)).y = y * cos(R_INC_MINUS) + z * sin(R_INC_MINUS);
		++i;
	}
	return (camera_perspective_project(scene), 1);
}

char	camera_rotation_x_plus(t_scene *scene)
{
	float	y;
	float	z;
	int		i;

	i = 0;
	(*scene).camera.rotation.x += R_INC_PLUS;
	y = (*scene).camera.position.y;
	z = (*scene).camera.position.z;
	(*scene).camera.position.z = (z * cos(R_INC_PLUS) - y * sin(R_INC_PLUS));
	(*scene).camera.position.y = (y * cos(R_INC_PLUS) + z * sin(R_INC_PLUS));
	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(R_INC_PLUS) - y * sin(R_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(R_INC_PLUS) + z * sin(R_INC_PLUS);
		++i;
	}
	return (camera_perspective_project(scene), 1);
}

char	camera_rotation_y_minus(t_scene *scene)
{
	float	x;
	float	z;
	int		i;

	i = 0;
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		-(*scene).camera.rotation.x);
	(*scene).camera.rotation.y += R_INC_MINUS;
	x = (*scene).camera.position.x;
	z = (*scene).camera.position.z;
	(*scene).camera.position.z = (z * cos(R_INC_MINUS) + x * sin(R_INC_MINUS));
	(*scene).camera.position.x = (x * cos(R_INC_MINUS) - z * sin(R_INC_MINUS));
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		(*scene).camera.rotation.x);
	while (i < (*scene).cloud_size)
	{
		rev_camera_rotation_x(scene, i, -(*scene).camera.rotation.x);
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(R_INC_MINUS) + x * sin(R_INC_MINUS);
		(*((*scene).cloud + i)).x = x * cos(R_INC_MINUS) - z * sin(R_INC_MINUS);
		rev_camera_rotation_x(scene, i, (*scene).camera.rotation.x);
		++i;
	}
	return (camera_perspective_project(scene), 1);
}

char	camera_rotation_y_plus(t_scene *scene)
{
	float	x;
	float	z;
	int		i;

	i = 0;
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		-(*scene).camera.rotation.x);
	(*scene).camera.rotation.y += R_INC_PLUS;
	x = (*scene).camera.position.x;
	z = (*scene).camera.position.z;
	(*scene).camera.position.z = (z * cos(R_INC_PLUS) + x * sin(R_INC_PLUS));
	(*scene).camera.position.x = (x * cos(R_INC_PLUS) - z * sin(R_INC_PLUS));
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		(*scene).camera.rotation.x);
	while (i < (*scene).cloud_size)
	{
		rev_camera_rotation_x(scene, i, -(*scene).camera.rotation.x);
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(R_INC_PLUS) + x * sin(R_INC_PLUS);
		(*((*scene).cloud + i)).x = x * cos(R_INC_PLUS) - z * sin(R_INC_PLUS);
		rev_camera_rotation_x(scene, i, (*scene).camera.rotation.x);
		++i;
	}
	return (camera_perspective_project(scene), 1);
}
