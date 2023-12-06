/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:52:09 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:54:31 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	nothing(t_scene *scene)
{
	(void)scene;
	return (1);
}

void	clear_color_buffer(long long int *color_buffer, float *z_buffer)
{
	int	i;

	i = 0;
	while (i < CLEAR_SIZE)
	{
		*(z_buffer + i) = (float)0xffffffff;
		*(color_buffer + i) = 0;
		++i;
	}
	while (i < BUFF_SIZE)
	{
		*(z_buffer + i) = (float)0xffffffff;
		++i;
	}
}
