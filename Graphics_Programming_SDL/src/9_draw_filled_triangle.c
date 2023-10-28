#include "header.h"

static void	draw_line(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{
	int start = x_start;

	while (x_start <= x_end)
	{
		(*pixel_info).cell = x_start + y;
		if (x_start == x_end || x_start == start)
			(*pixel_info).color = 0xFF000000;
		else
			(*pixel_info).color = 0xFF808080;
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE && *((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) > (*pixel_info).depth)
		](pixel_info);
		++x_start;
	}
}

static void	draw_line2(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{
	int start = x_end;
	
	while (x_end <= x_start)
	{
		if (x_start == x_end || x_end == start)
			(*pixel_info).color = 0xFF000000;
		else	
			(*pixel_info).color = 0xFF808080;
		(*pixel_info).cell = x_end + y;
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE && *((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) > (*pixel_info).depth)
		](pixel_info);
		++x_end;
	}
}

static void	fill_flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *m)
{
	float	inv_sloap_1;
	float	inv_sloap_2;
	float	x_start;
	float	x_end;
	int		y;

	inv_sloap_1 = ((*p1).x - (*p0).x) / (float)((*p1).y - (*p0).y);
	inv_sloap_2 = ((*m).x - (*p0).x) / (float)((*m).y - (*p0).y);
	x_start = (*p0).x;
	x_end = (*p0).x;
	y = (*p0).y;
//printf("y = %d, m.y = %d\n", y, (*m).y);
	while (y <= (*m).y)
	{
		
		//printf("x_start = %f, x_end = %f\n", x_start, x_end);
		if (x_start < x_end)
			draw_line(round(x_start), round(x_end), ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(round(x_start), round(x_end), ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end += inv_sloap_2;
		++y;
	}
}

static void	fill_flat_top(t_pixel_info *pixel_info, t_point *p2, t_point *p1, t_point *m)
{
	float	inv_sloap_1;
	float	inv_sloap_2;
	float	x_start;
	float	x_end;
	int		y;

	inv_sloap_1 = ((*p1).x - (*p2).x) / (float)((*p2).y - (*p1).y);
	inv_sloap_2 = ((*m).x - (*p2).x) / (float)((*p2).y - (*m).y);
	x_start = (*p2).x;
	x_end = (*p2).x;
	y = (*p2).y;
//printf("y = %d, m.y = %d\n", y, (*m).y);
	while (y > (*m).y)
	{
		//printf("x_start = %f, x_end = %f\n", x_start, x_end);
		if (x_start < x_end)
			draw_line(round(x_start), round(x_end), ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(round(x_start), round(x_end), ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end += inv_sloap_2;
		--y;
	}
}

void	flat_bottom_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2)
{
	t_point	m;
	m.y = (*p1).y;
	m.x = (((*p2).x - (*p0).x) * ((*p1).y - (*p0).y)) / ((*p2).y - (*p0).y) + (*p0).x;
	fill_flat_bottom(pixel_info, p0, p1, &m);
	fill_flat_top(pixel_info, p2, p1, &m);
}

void	flat_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2)
{
		fill_flat_top(pixel_info, p2, p1, p0);
}

void	flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2)
{
		fill_flat_bottom(pixel_info, p0, p1, p2);
}

static void	draw_filled_triangle(t_point *p0, t_point *p1, t_point *p2, t_pixel_info *pixel_info)
{
//printf("\tp0 = (%d,%d), p1 = (%d,%d), p2 = (%d,%d)\n", (*p0).x, (*p0).y, (*p1).x, (*p1).y, (*p2).x, (*p2).y);
	//TODO : calculate face depth
	(*pixel_info).depth = (*p0).z + (*p1).z + (*p2).z;
	(*(*(*pixel_info).scene).fun).flat_top_or_bottom[
		((*p1).y == (*p0).y)
		+ (((*p1).y == (*p2).y && ((*p1).y != (*p0).y)) << 1)
	](pixel_info, p0, p1, p2);
//printf("\n----------------------------\n\n");
}

void	draw_ft012(t_pixel_info *pixel_info, int i)
{
//printf("012:\n");
//printf("p0 = (%d), p1 = (%d), p2 = (%d)\n", ((*((*(*pixel_info).scene).projected_triangle + i))).p0.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p1.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p2.y);
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		pixel_info
	);
}

void	draw_ft021(t_pixel_info *pixel_info, int i)
{
//printf("021:\n");
//printf("p0 = (%d), p1 = (%d), p2 = (%d)\n", ((*((*(*pixel_info).scene).projected_triangle + i))).p0.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p1.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p2.y);
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		pixel_info
	);
}

void	draw_ft102(t_pixel_info *pixel_info, int i)
{
//printf("102:\n");
//printf("p0 = (%d), p1 = (%d), p2 = (%d)\n", ((*((*(*pixel_info).scene).projected_triangle + i))).p0.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p1.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p2.y);
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		pixel_info
	);
}

void	draw_ft120(t_pixel_info *pixel_info, int i)
{
//printf("120:\n");
//printf("p0 = (%d), p1 = (%d), p2 = (%d)\n", ((*((*(*pixel_info).scene).projected_triangle + i))).p0.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p1.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p2.y);
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		pixel_info
	);
}

void	draw_ft201(t_pixel_info *pixel_info, int i)
{
//printf("201:\n");
//printf("p0 = (%d), p1 = (%d), p2 = (%d)\n", ((*((*(*pixel_info).scene).projected_triangle + i))).p0.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p1.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p2.y);
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		pixel_info
	);
}

void	draw_ft210(t_pixel_info *pixel_info, int i)
{
//printf("210:\n");
//printf("p0 = (%d), p1 = (%d), p2 = (%d)\n", ((*((*(*pixel_info).scene).projected_triangle + i))).p0.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p1.y, ((*((*(*pixel_info).scene).projected_triangle + i))).p2.y);
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		pixel_info
	);
}
