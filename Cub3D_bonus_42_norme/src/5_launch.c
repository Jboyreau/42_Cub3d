/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_launch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:31:51 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 17:36:40 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	sort_vertices2(t_scene *scene, int i)
{
	return (((((*((*scene).projected_triangle + i)).p0.y
					< (*((*scene).projected_triangle + i)).p1.y)
				&& ((*((*scene).projected_triangle + i)).p1.y
					== (*((*scene).projected_triangle + i)).p2.y)))
		+ ((((*((*scene).projected_triangle + i)).p0.y
					> (*((*scene).projected_triangle + i)).p1.y)
				&& ((*((*scene).projected_triangle + i)).p1.y
					== (*((*scene).projected_triangle + i)).p2.y)) << 2)
		+ ((((*((*scene).projected_triangle + i)).p1.y
					< (*((*scene).projected_triangle + i)).p0.y)
				&& ((*((*scene).projected_triangle + i)).p0.y
					== (*((*scene).projected_triangle + i)).p2.y)) << 1)
		+ ((((*((*scene).projected_triangle + i)).p1.y
					> (*((*scene).projected_triangle + i)).p0.y)
				&& ((*((*scene).projected_triangle + i)).p0.y
					== (*((*scene).projected_triangle + i)).p2.y)))
		+ ((((*((*scene).projected_triangle + i)).p2.y
					< (*((*scene).projected_triangle + i)).p1.y)
				&& ((*((*scene).projected_triangle + i)).p1.y
					== (*((*scene).projected_triangle + i)).p0.y)) << 3)
		+ ((((*((*scene).projected_triangle + i)).p2.y
					> (*((*scene).projected_triangle + i)).p1.y)
				&& ((*((*scene).projected_triangle + i)).p1.y
					== (*((*scene).projected_triangle + i)).p0.y)) << 1));
}

static int	sort_vertices(t_scene *scene, int i)
{
	return ((((*((*scene).projected_triangle + i)).p0.y
				< (*((*scene).projected_triangle + i)).p2.y)
			&& ((*((*scene).projected_triangle + i)).p2.y
				< (*((*scene).projected_triangle + i)).p1.y))
		+ ((((*((*scene).projected_triangle + i)).p1.y
					< (*((*scene).projected_triangle + i)).p0.y)
				&& ((*((*scene).projected_triangle + i)).p0.y
					<= (*((*scene).projected_triangle + i)).p2.y)) << 1)
		+ ((((*((*scene).projected_triangle + i)).p1.y
					< (*((*scene).projected_triangle + i)).p2.y)
				&& ((*((*scene).projected_triangle + i)).p2.y
					< (*((*scene).projected_triangle + i)).p0.y)) << 2)
		+ ((((*((*scene).projected_triangle + i)).p2.y
					< (*((*scene).projected_triangle + i)).p0.y)
				&& ((*((*scene).projected_triangle + i)).p0.y
					< (*((*scene).projected_triangle + i)).p1.y)) << 3)
		+ ((((*((*scene).projected_triangle + i)).p2.y
					< (*((*scene).projected_triangle + i)).p1.y)
				&& ((*((*scene).projected_triangle + i)).p1.y
					< (*((*scene).projected_triangle + i)).p0.y)) << 4)
		+ sort_vertices2(scene, i));
}

void	launch(t_scene *scene, t_pixel_info *pixel_info, int i)
{
	(*(*scene).fun).draw_ft[
			sort_vertices(scene, i)](pixel_info, i);
}
