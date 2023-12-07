/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_clipping2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:07:45 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 20:16:12 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	inter_p_outside(t_scene *scene, t_line *cp, t_v2 *dot,
t_v3_uv *inside_vertices)
{
	float	t;
	t_v3_uv	q12;

	t = ((*dot).x / ((*dot).x - (*dot).y));
	q12 = vec3uv_subtract((*cp).cur, (*cp).prev);
	q12 = vec3uv_multiplication(&q12, t);
	*(inside_vertices + (*scene).inside_size) = vec3uv_addition((*cp).prev,
			&q12);
	(*(inside_vertices + (*scene).inside_size)).u = (*(*cp).prev).u
		+ t * ((*(*cp).cur).u - (*(*cp).prev).u);
	(*(inside_vertices + (*scene).inside_size)).v = (*(*cp).prev).v
		+ t * ((*(*cp).cur).v - (*(*cp).prev).v);
	*(inside_vertices + (*scene).inside_size + 1) = *((*cp).cur);
	(*scene).inside_size += 2;
}

void	inter_c_outside(t_scene *scene, t_line *cp, t_v2 *dot,
t_v3_uv *inside_vertices)
{
	float	t;
	t_v3_uv	q12;

	t = ((*dot).x / ((*dot).x - (*dot).y));
	q12 = vec3uv_subtract((*cp).cur, (*cp).prev);
	q12 = vec3uv_multiplication(&q12, t);
	*(inside_vertices + (*scene).inside_size) = vec3uv_addition((*cp).prev,
			&q12);
	(*(inside_vertices + (*scene).inside_size)).u = (*(*cp).prev).u
		+ t * ((*(*cp).cur).u - (*(*cp).prev).u);
	(*(inside_vertices + (*scene).inside_size)).v = (*(*cp).prev).v
		+ t * ((*(*cp).cur).v - (*(*cp).prev).v);
	++(*scene).inside_size;
}

void	inter_both_inside(t_scene *scene, t_line *cp, t_v2 *dot,
t_v3_uv *inside_vertices)
{
	(void)dot;
	*(inside_vertices + (*scene).inside_size) = *((*cp).cur);
	++(*scene).inside_size;
}

void	inter_both_outside(t_scene *scene, t_line *cp, t_v2 *dot,
t_v3_uv *inside_vertices)
{
	(void)scene;
	(void)cp;
	(void)dot;
	(void)inside_vertices;
}
