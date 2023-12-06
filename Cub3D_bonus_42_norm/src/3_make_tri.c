/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_make_tri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:29:57 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 20:11:09 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	print_triangle_index(t_tri *triangle_index, char *obj, t_tex2 *vt,
t_index *i)
{
	(*i).i += 2;
	(*(triangle_index + (*i).j)).a = atoi(obj + (*i).i) - 1;
	(*(triangle_index + (*i).j)).texture = (*i).index + ((*i).index == -1);
	while (*(obj + (*i).i) != '/')
		++((*i).i);
	(*(triangle_index + (*i).j)).uv_a = *(vt + atoi(obj + (++((*i).i))) - 1);
	while (*(obj + (*i).i) != ' ')
		++((*i).i);
	(*(triangle_index + (*i).j)).b = atoi(obj + (++((*i).i))) - 1;
	while (*(obj + (*i).i) != '/')
		++((*i).i);
	(*(triangle_index + (*i).j)).uv_b = *(vt + atoi(obj + (++((*i).i))) - 1);
	while (*(obj + (*i).i) != ' ')
		++((*i).i);
	(*(triangle_index + (*i).j)).c = atoi(obj + (++((*i).i))) - 1;
	while (*(obj + (*i).i) != '/')
		++((*i).i);
	(*(triangle_index + (*i).j)).uv_c = *(vt + atoi(obj + (++((*i).i))) - 1);
	while ((*(obj + (*i).i) && *(obj + (*i).i) != '\n'))
		++((*i).i);
	++((*i).j);
}

static int	skip_comment(char *obj, t_index *i)
{
	while (*(obj + (++((*i).i))) && *(obj + (*i).i) != '\n')
		;
	if (*(obj + (*i).i))
		++((*i).i);
	else
		return (0);
	return (1);
}

static int	find_side(char *obj, t_index *i)
{
	if (check_material(obj + (*i).i))
		++((*i).index);
	if (*(obj + (*i).i) == 'f' && *(obj + (*i).i + 1) == ' ')
		return (0);
	++((*i).i);
	return (1);
}

int	make_triangle_index(t_tri *triangle_index, char *obj, t_tex2 *vt, int part)
{
	t_index	i;

	make_vt(obj, vt);
	i.i = 0;
	i.j = 0;
	i.index = part;
	while (*(obj + i.i))
		if (find_side(obj, &i) == 0)
			break ;
	while (1)
	{
		if (check_material(obj + i.i))
			++(i.index);
		if (*(obj + i.i) == '#')
			if (skip_comment(obj, &i) == 0)
				break ;
		if (*(obj + i.i) == 'f' && *(obj + i.i + 1) == ' ')
			print_triangle_index(triangle_index, obj, vt, &i);
		if (*(obj + i.i) == 0)
			break ;
		++(i.i);
	}
	return (i.j);
}
