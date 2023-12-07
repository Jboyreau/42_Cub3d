/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_translation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:26:27 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 17:40:40 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	perspective_project_down(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		-(*scene).camera.rotation.x);
	(*scene).camera.position.y += DIST_INC;
	(*scene).pos_incy = DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		(*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_up(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		-(*scene).camera.rotation.x);
	(*scene).camera.position.y -= DIST_INC;
	(*scene).pos_incy = -DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		(*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_right(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		-(*scene).camera.rotation.x);
	(*scene).camera.position.x += DIST_INC;
	(*scene).pos_incx = DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		(*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_left(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		-(*scene).camera.rotation.x);
	(*scene).camera.position.x -= DIST_INC;
	(*scene).pos_incx = -DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		(*scene).camera.rotation.x);
	return (perspective_project(scene));
}
