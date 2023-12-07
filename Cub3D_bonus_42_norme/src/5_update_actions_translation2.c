/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions_translation2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:27:17 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 17:39:07 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	perspective_project_far(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		-(*scene).camera.rotation.x);
	(*scene).camera.position.z += DIST_INC;
	(*scene).pos_incz = DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		(*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_close(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		-(*scene).camera.rotation.x);
	(*scene).camera.position.z -= DIST_INC;
	(*scene).pos_incz = -DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position),
		(*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_zoom_plus(t_scene *scene)
{
	(*scene).scale += SCALE_INC * ((*scene).scale + SCALE_INC < 1000);
	return (perspective_project(scene));
}

char	perspective_project_zoom_minus(t_scene *scene)
{
	(*scene).scale -= SCALE_INC;
	return (perspective_project(scene));
}
