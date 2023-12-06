/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_scene2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:27:03 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 17:29:07 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	affect_wall(t_scene *scene)
{
	(*scene).cloud_size_wall = (*scene).cloud_size_temp;
	(*scene).triangle_index_size_wall = (*scene).triangle_index_size_temp;
	(*scene).cloud_wall = (*scene).cloud_temp;
	(*scene).triangle_index_wall = (*scene).triangle_index_temp;
}

void	affect_floor(t_scene *scene)
{
	(*scene).cloud_size_floor = (*scene).cloud_size_temp;
	(*scene).triangle_index_size_floor = (*scene).triangle_index_size_temp;
	(*scene).cloud_floor = (*scene).cloud_temp;
	(*scene).triangle_index_floor = (*scene).triangle_index_temp;
}

void	affect_roof(t_scene *scene)
{
	(*scene).cloud_size_roof = (*scene).cloud_size_temp;
	(*scene).triangle_index_size_roof = (*scene).triangle_index_size_temp;
	(*scene).cloud_roof = (*scene).cloud_temp;
	(*scene).triangle_index_roof = (*scene).triangle_index_temp;
}
