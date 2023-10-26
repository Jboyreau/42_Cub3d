#include "header.h"

void	fill_flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_poin *p1, t_poin *m)
{
	float inv_sloap_1;
	float inv_sloap_2;
	float x_start;
	float x_end;
	int y;

	inv_sloap_1 = ((*p1).x - (*p0).x) / (float)((*p1).y - (*p0).y);
	inv_sloap_2 = ((*p1).x - (*m).x) / (float)((*p1).y - (*m).y);
	y = -1;
	while (++y <= (*m).y)
	{
		//draw_line(x_start, x_end, pixel_info);
		x_start += inv_sloap_1;
		x_end += inv_sloap_2;
	}
}

void	fill_flat_top(t_point *p1, t_poin *p2, t_poin *m)
{
	//TODO:
}

void	draw_ft012(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*pixel_info).(*((*scene).projected_triangle + i))).p0,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p1,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p2,
		pixel_info
	);
}

void	draw_ft021(t_pixel_info *pixel_info, int i)
{
	t_scene_pixel_info	scene_pixel_info;

	scene_pixel_info.scene = scene;
	scene_pixel_info.pixel_info = pixel_info;
	draw_filled_triangle(
		&((*pixel_info).(*((*scene).projected_triangle + i))).p0,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p2,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p1,
		pixel_info
	);
}

void	draw_ft102(t_pixel_info *pixel_info, int i)
{
	t_scene_pixel_info	scene_pixel_info;

	scene_pixel_info.scene = scene;
	scene_pixel_info.pixel_info = pixel_info;
	draw_filled_triangle(
		&((*pixel_info).(*((*scene).projected_triangle + i))).p1,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p0,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p2,
		pixel_info
	);
}

void	draw_ft120(t_pixel_info *pixel_info, int i)
{
	t_scene_pixel_info	scene_pixel_info;

	scene_pixel_info.scene = scene;
	scene_pixel_info.pixel_info = pixel_info;
	draw_filled_triangle(
		&((*pixel_info).(*((*scene).projected_triangle + i))).p1,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p2,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p0,
		pixel_info
	);
}

void	draw_ft201(t_pixel_info *pixel_info, int i)
{
	t_scene_pixel_info	scene_pixel_info;

	scene_pixel_info.scene = scene;
	scene_pixel_info.pixel_info = pixel_info;
	draw_filled_triangle(
		&((*pixel_info).(*((*scene).projected_triangle + i))).p2,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p0,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p1,
		pixel_info
	);
}

void	draw_ft210(t_pixel_info *pixel_info, int i)
{
	t_scene_pixel_info	scene_pixel_info;

	scene_pixel_info.scene = scene;
	scene_pixel_info.pixel_info = pixel_info;
	draw_filled_triangle(
		&((*pixel_info).(*((*scene).projected_triangle + i))).p2,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p1,
		&((*pixel_info).(*((*scene).projected_triangle + i))).p0,
		pixel_info
	);
}

void	draw_filled_triangle(t_point *p0, t_point *p1, t_point *p2, *t_pixel_info pixel_info)
{
	t_point	m;

	m.y = (*p1).y;
	m.x = ((((*p2).x - (*p0).x) * ((*p1).y - (*p0).y)) / ((*p2).y - (*p0).y)) + (*p0).x;
	//TODO :fill flat bottom
	fill_flat_bottom(p0, p1, &M);
	//TODO :fill flat top
	fill_flat_top(p1, &M, p2);
}
