/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_clipping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:07:25 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 20:56:49 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	poly_to_tri(t_scene *scene, t_v3_uv *poly)
{
	int	i;

	(*scene).nb_tri = 0;
	i = -1;
	while (++i < (*scene).poly_size - 2)
	{
		uv_tv3(&(*((*scene).projected_triangle + (*scene).nb_tri)).a, poly);
		(*((*scene).projected_triangle + (*scene).nb_tri)).p0.uv.u = (*poly).u;
		(*((*scene).projected_triangle + (*scene).nb_tri)).p0.uv.v = (*poly).v;
		uv_tv3(&(*((*scene).projected_triangle + (*scene).nb_tri)).b, poly
			+ i + 1);
		(*((*scene).projected_triangle + (*scene).nb_tri)).p1.uv.u = (*(poly
					+ i + 1)).u;
		(*((*scene).projected_triangle + (*scene).nb_tri)).p1.uv.v = (*(poly
					+ i + 1)).v;
		uv_tv3(&(*((*scene).projected_triangle + (*scene).nb_tri)).c, poly
			+ i + 2);
		(*((*scene).projected_triangle + (*scene).nb_tri)).p2.uv.u = (*(poly
					+ i + 2)).u;
		(*((*scene).projected_triangle + (*scene).nb_tri)).p2.uv.v = (*(poly
					+ i + 2)).v;
		++(*scene).nb_tri;
	}
}

static	void	clip(t_scene *scene, t_plane *plane, t_v3_uv **poly,
t_v3_uv **ins_vert)
{
	t_line		cp;
	t_v2		dot;
	t_v3_uv		*temp;

	cp.cur = *poly;
	cp.prev = *poly + (*scene).poly_size - 1;
	cp.vec_cur = vec3uv_subtract(cp.cur, &((*plane).point));
	cp.vec_prev = vec3uv_subtract(cp.prev, &((*plane).point));
	dot.x = vec3uv_dot(&(cp.vec_prev), &((*plane).n));
	(*scene).inside_size = 0;
	while (cp.cur != (*poly) + (*scene).poly_size)
	{
		cp.vec_cur = vec3uv_subtract(cp.cur, &((*plane).point));
		dot.y = vec3uv_dot(&(cp.vec_cur), &((*plane).n));
		(*(*scene).fun).inter[
			(dot.y >= 0 && dot.x < 0)
			+ ((dot.x >= 0 && dot.y < 0) << 1)
			+ ((dot.y >= 0 && dot.x >= 0) << 2)
		](scene, &cp, &dot, *ins_vert);
		dot.x = dot.y;
		cp.prev = cp.cur;
		++(cp.cur);
	}
	(*scene).poly_size = (*scene).inside_size;
	return (temp = *poly, *poly = *ins_vert, *ins_vert = temp, (void)0);
}

t_v3_uv	*tri_to_poly(t_scene *scene, t_tri *face)
{
	t_v3_uv	*pt_poly;
	t_v3_uv	*pt_ins_vert;

	pt_poly = (*scene).poly;
	pt_ins_vert = (*scene).inside_vertices;
	tv3_uv((*scene).poly, (*scene).cloud + (*face).a);
	face_uv((*scene).poly, &(*face).uv_a);
	tv3_uv((*scene).poly + 1, (*scene).cloud + (*face).b);
	face_uv((*scene).poly + 1, &(*face).uv_b);
	tv3_uv((*scene).poly + 2, (*scene).cloud + (*face).c);
	face_uv((*scene).poly + 2, &(*face).uv_c);
	(*scene).poly_size = 3;
	clip(scene, &((*scene).view.near), &pt_poly, &pt_ins_vert);
	clip(scene, &((*scene).view.far), &pt_poly, &pt_ins_vert);
	clip(scene, &((*scene).view.left), &pt_poly, &pt_ins_vert);
	clip(scene, &((*scene).view.right), &pt_poly, &pt_ins_vert);
	clip(scene, &((*scene).view.top), &pt_poly, &pt_ins_vert);
	clip(scene, &((*scene).view.bottom), &pt_poly, &pt_ins_vert);
	return ((*scene).poly);
}
