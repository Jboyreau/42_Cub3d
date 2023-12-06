/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_scene3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:27:18 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 17:34:35 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_camera(t_scene *scene)
{
	(*scene).camera.position.x = X_VALUE;
	(*scene).camera.position.y = Y_VALUE;
	(*scene).camera.position.z = Z_VALUE;
	(*scene).camera.fov_w = 1.135;
	(*scene).camera.fov_h = 0.68;
	(*scene).camera.rotation.x = 0;
	(*scene).camera.rotation.y = 0;
	(*scene).camera.rotation.z = 0;
}

static void	init_plane2(t_scene *scene, t_v3 *origin, float fov_w, float fov_h)
{
	tv3_uv(&(*scene).view.right.point, origin);
	(*scene).view.right.n.x = -cos(fov_w);
	(*scene).view.right.n.y = 0;
	(*scene).view.right.n.z = sin(fov_w);
	tv3_uv(&(*scene).view.left.point, origin);
	(*scene).view.left.n.x = cos(fov_w);
	(*scene).view.left.n.y = 0;
	(*scene).view.left.n.z = sin(fov_w);
	tv3_uv(&(*scene).view.top.point, origin);
	(*scene).view.top.n.x = 0;
	(*scene).view.top.n.y = cos(fov_h);
	(*scene).view.top.n.z = sin(fov_h);
	tv3_uv(&(*scene).view.bottom.point, origin);
	(*scene).view.bottom.n.x = 0;
	(*scene).view.bottom.n.y = -cos(fov_h);
	(*scene).view.bottom.n.z = sin(fov_h);
}

void	init_plane(t_scene *scene)
{
	static t_v3	origin = {0, 0, 0, 0};
	float		fov_h;
	float		fov_w;

	fov_h = (*scene).camera.fov_h / 2;
	fov_w = (*scene).camera.fov_w / 2;
	tv3_uv(&(*scene).view.near.point, &origin);
	(*scene).view.near.point.z = Z_MIN;
	(*scene).view.near.n.x = 0;
	(*scene).view.near.n.y = 0;
	(*scene).view.near.n.z = 1;
	tv3_uv(&(*scene).view.far.point, &origin);
	(*scene).view.far.point.z = Z_MAX;
	(*scene).view.far.n.x = 0;
	(*scene).view.far.n.y = 0;
	(*scene).view.far.n.z = -1;
	init_plane2(scene, &origin, fov_w, fov_h);
}
