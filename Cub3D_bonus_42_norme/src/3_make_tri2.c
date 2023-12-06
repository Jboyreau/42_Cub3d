/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_make_tri2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:35:21 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 20:10:08 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	print_uv(char *obj, t_tex2 *vt, int *i, int *j)
{
	*i += 3;
	(*(vt + *j)).u = strtof(obj + *i, NULL);
	while (*(obj + *i) != ' ')
		++(*i);
	(*(vt + *j)).v = 1 - strtof(obj + (++(*i)), NULL);
	while ((*(obj + *i) && *(obj + *i) != '\n'))
		++(*i);
	++(*j);
}

static int	skip_com(char *obj, int *i)
{
	while (*(obj + ++(*i)) && *(obj + *i) != '\n')
		;
	if (*(obj + *i))
		++(*i);
	else
		return (0);
	return (1);
}

void	make_vt(char *obj, t_tex2 *vt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*(obj + i))
	{
		if (*(obj + i) == 'v' && *(obj + i + 1) == 't' && *(obj + i + 2) == ' ')
			break ;
		++i;
	}
	while (1)
	{
		if (*(obj + i) == '#')
			if (skip_com(obj, &i) == 0)
				break ;
		if (*(obj + i) == 'v' && *(obj + i + 1) == 't' && *(obj + i + 2) == ' ')
			print_uv(obj, vt, &i, &j);
		if (*(obj + i) == 0)
			break ;
		++i;
	}
}

char	check_material(char *str)
{
	char	*material;
	int		j;

	j = 0;
	material = "usemtl";
	while (j < 6 && *(str + j) == *(material + j))
		++j;
	return (j == 6);
}
