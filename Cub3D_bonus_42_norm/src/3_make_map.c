/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_make_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:34:58 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/06 23:33:13 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	allocate_model(t_scene *scene, int i, int n_wall)
{
	int	map_size;
	int	n_fr;

	map_size = (*scene).line_len * (*scene).line_nb;
	while (++i < map_size)
		if (*((*scene).map + i) == '1')
			++n_wall;
	n_fr = 0;
	i = -1;
	while (++i < map_size)
		if (*((*scene).map + i) != '?')
			++n_fr;
	(*scene).cloud_size = n_wall * (*scene).cloud_size_wall
		+ n_fr * (*scene).cloud_size_floor
		+ n_fr * (*scene).cloud_size_roof;
	(*scene).cloud = malloc((*scene).cloud_size * sizeof(t_v3));
	if ((*scene).cloud == NULL)
		return (0);
	(*scene).triangle_index_size = n_wall * (*scene).triangle_index_size_wall
		+ n_fr * (*scene).triangle_index_size_floor
		+ n_fr * (*scene).triangle_index_size_roof;
	(*scene).triangle_index = malloc((*scene).triangle_index_size
			* sizeof(t_tri));
	return (1 * ((*scene).triangle_index != NULL));
}

static void	init_stuff(t_scene *scene)
{
	(*scene).map = NULL;
	(*scene).line_len = 0;
	(*scene).line_nb = 0;
}

static void	p(char *str, int len)
{
	write(2, str, len);
}

int	assemble_map(t_scene *scene)
{
	static char	*map_raw = NULL;
	static char	*e = "Error\nWrong texture descriptor.\n";

	init_stuff(scene);
	map_raw = load_map((*scene).map_path, 0, 0, NULL);
	if (map_raw == NULL)
		return (d(scene, map_raw), p("Error\nLoad map failed.\n", 24), 0);
	if (get_texture(scene, map_raw) == 0)
		return (d(scene, map_raw), p(e, 33), 0);
	set_map_size(map_raw, &((*scene).line_len), &((*scene).line_nb));
	if ((*scene).line_len < 3 || (*scene).line_nb < 3)
		return (d(scene, map_raw), p("Error\nEmpty map.\n", 17), 0);
	if (process_map(scene, map_raw, (*scene).line_len, (*scene).line_nb) == 0)
		return (d(scene, map_raw), p("Error\nProcess map failed.\n", 26), 0);
	if (is_valid(scene) == 0)
		return (d(scene, map_raw), p("Error\nMap is invalid.\n", 23), 0);
	if (allocate_model(scene, -1, 0) == 0)
		return (d(scene, map_raw), 0);
	assemble(scene);
	return (d(scene, map_raw), 1);
}
