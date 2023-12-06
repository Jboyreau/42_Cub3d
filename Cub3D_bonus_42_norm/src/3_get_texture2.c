/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:19:35 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:20:02 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	write_tex(char *map_raw, t_scene *scene, int index, int j)
{
	if (index == 0)
		*((*scene).tno + j) = *(map_raw);
	else if (index == 1)
		*((*scene).tso + j) = *(map_raw);
	else if (index == 2)
		*((*scene).tea + j) = *(map_raw);
	else if (index == 3)
		*((*scene).twe + j) = *(map_raw);
	else if (index == 4)
		*((*scene).tf + j) = *(map_raw);
	else if (index == 5)
		*((*scene).tr + j) = *(map_raw);
}

void	write_tex_end(t_scene *scene, int index, int j)
{
	if (index == 0)
		*((*scene).tno + j) = 0;
	else if (index == 1)
		*((*scene).tso + j) = 0;
	else if (index == 2)
		*((*scene).tea + j) = 0;
	else if (index == 3)
		*((*scene).twe + j) = 0;
	else if (index == 4)
		*((*scene).tf + j) = 0;
	else if (index == 5)
		*((*scene).tr + j) = 0;
}
