/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_fun3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:20:33 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 17:25:39 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initialize_inter(void (*inter[])(t_scene *scene, t_line *cp,
t_v2 *dot, t_v3_uv *inside_vertices))
{
	inter[0] = &inter_both_outside;
	inter[1] = &inter_p_outside;
	inter[2] = &inter_c_outside;
	inter[4] = &inter_both_inside;
}
