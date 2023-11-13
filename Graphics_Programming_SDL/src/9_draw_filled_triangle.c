#include "header.h"

int	find_color(t_v3 *weight, int *texture, t_pixel_info *pixel_info)
{
	float	interpolated_u;
	float	interpolated_v;
	int		tw;
	int		th;
	int		x;
	int		y;

	tw = (*(*pixel_info).scene).tex_w;
	th = (*(*pixel_info).scene).tex_h;
	interpolated_u = (*weight).x * (*pixel_info).p0.uv.u + (*weight).y * (*pixel_info).p1.uv.u + (*weight).z * (*pixel_info).p2.uv.u;
//printf("u = %f * %f + %f * %f + %f * %f\n", (*weight).x, (*pixel_info).p0.uv.u, (*weight).y, (*pixel_info).p1.uv.u, (*weight).z, (*pixel_info).p2.uv.u);
	interpolated_v = (*weight).x * (*pixel_info).p0.uv.v + (*weight).y * (*pixel_info).p1.uv.v + (*weight).z * (*pixel_info).p2.uv.v;
//printf("u = %f * %f + %f * %f + %f * %f\n", (*weight).x, (*pixel_info).p0.uv.v, (*weight).y, (*pixel_info).p1.uv.v, (*weight).z, (*pixel_info).p2.uv.v);
	x = abs((int)(interpolated_u * (tw - 1))); //printf("x = %d\n", x);
	y = abs((int)(interpolated_v * (th - 1))); //printf("y = %d\n", y);
	x = x * (x < 64 && x > 0);
	y = y * (y < 64 && x > 0);
	return (*(texture + y * tw + x));
}

t_v3	*barycentric_weight(t_pixel_info* pixel_info)
{
	static t_v3	weight;
	t_br		ref;

	ref.ac = vec2_subtract(&(*pixel_info).c, &(*pixel_info).a);
	ref.ab = vec2_subtract(&(*pixel_info).b, &(*pixel_info).a);
	ref.ap = vec2_subtract(&(*pixel_info).p, &(*pixel_info).a);
	ref.pc = vec2_subtract(&(*pixel_info).c, &(*pixel_info).p);
	ref.pb = vec2_subtract(&(*pixel_info).b, &(*pixel_info).p);
	//printf("\n--------------------------\n");
	ref.para_abc = (ref.ac.x * ref.ab.y) - (ref.ac.y * ref.ab.x);// printf("ref_abc %f\n", ref.para_abc);
	ref.alpha = (ref.pc.x * ref.pb.y - ref.pc.y * ref.pb.x) / ref.para_abc;// printf("ref_alpha %f\n", ref.alpha);
	ref.beta = (ref.ac.x * ref.ap.y - ref.ac.y * ref.ap.x) / ref.para_abc;// printf("ref_beta %f\n", ref.beta);
	ref.gamma = 1 - ref.alpha - ref.beta;// printf("ref_gamma %f\n", ref.gamma);
	weight.x = ref.alpha;
	weight.y = ref.beta;
	weight.z = ref.gamma;
	return (&weight);
}

static void	draw_line(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{
	while (x_start <= x_end)
	{
		(*pixel_info).p.x = x_start;
		(*pixel_info).p.y = (*pixel_info).y;
		(*pixel_info).color = find_color(barycentric_weight(pixel_info), (*(*pixel_info).scene).texture, pixel_info);
		(*pixel_info).cell = x_start + y;
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			(*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) > (*pixel_info).depth)
		](pixel_info);
		++x_start;
	}
}

static void	draw_line2(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{	
	while (x_end <= x_start)
	{
		(*pixel_info).p.x = x_end;
		(*pixel_info).p.y = (*pixel_info).y;
		(*pixel_info).color = find_color(barycentric_weight(pixel_info), (*(*pixel_info).scene).texture, pixel_info);
		(*pixel_info).cell = x_end + y;
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			(*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) > (*pixel_info).depth)
		](pixel_info);
		++x_end;
	}
}

static void	fill_flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *m)
{
	float	inv_sloap_1;
	float	x_start;
	float	x_end;
	int		y;

	inv_sloap_1 = ((*p1).x - (*p0).x) / (float)((*p1).y - (*p0).y);
	x_start = (*p0).x;
	x_end = (*p0).x;
	y = (*p0).y;
	while (y <= (*m).y)
	{
		(*pixel_info).y = y;
		if (x_start < x_end)
			draw_line(round(x_start), round(x_end), ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(round(x_start), round(x_end), ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end += (*(*pixel_info).scene).inv_sloap_2;
		++y;
	}
}

static void	fill_flat_top(t_pixel_info *pixel_info, t_point *p2, t_point *p1, t_point *m)
{
	float	inv_sloap_1;
	float	x_start;
	float	x_end;
	int		y;

	inv_sloap_1 = ((*p1).x - (*p2).x) / (float)((*p2).y - (*p1).y);
	x_start = (*p2).x;
	x_end = (*p2).x;
	y = (*p2).y;
	while (y >= (*m).y)
	{
		(*pixel_info).y = y;
		if (x_start < x_end)
			draw_line(round(x_start), round(x_end), ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(round(x_start), round(x_end), ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end -= (*(*pixel_info).scene).inv_sloap_2;
		--y;
	}
}

void	flat_bottom_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2)
{
	t_point	m;
	m.y = (*p1).y;
	m.x = (((*p2).x - (*p0).x) * ((*p1).y - (*p0).y)) / ((*p2).y - (*p0).y) + (*p0).x;
	(*(*pixel_info).scene).inv_sloap_2 = ((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y);
	fill_flat_bottom(pixel_info, p0, p1, &m);
	fill_flat_top(pixel_info, p2, p1, &m);
}

void	flat_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2)
{
	(*(*pixel_info).scene).inv_sloap_2 = ((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y);
	fill_flat_top(pixel_info, p2, p1, p0);
}

void	flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2)
{
	(*(*pixel_info).scene).inv_sloap_2 = ((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y);
	fill_flat_bottom(pixel_info, p0, p1, p2);
}

static void	draw_filled_triangle(t_point *p0, t_point *p1, t_point *p2, t_pixel_info *pixel_info)
{
	(*pixel_info).a.x = (float)(*p0).x;
	(*pixel_info).a.y = (float)(*p0).y;
	(*pixel_info).b.x = (float)(*p1).x;
	(*pixel_info).b.y = (float)(*p1).y;
	(*pixel_info).c.x = (float)(*p2).x;
	(*pixel_info).c.y = (float)(*p2).y;
	(*pixel_info).p0 = (*p0);
	(*pixel_info).p1 = (*p1);
	(*pixel_info).p2 = (*p2);
	(*(*(*pixel_info).scene).fun).flat_top_or_bottom[
		((*p1).y == (*p0).y)
		+ (((*p1).y == (*p2).y && ((*p1).y != (*p0).y)) << 1)
	](pixel_info, p0, p1, p2);
}

void	draw_ft012(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		pixel_info
	);
}

void	draw_ft021(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		pixel_info
	);
}

void	draw_ft102(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		pixel_info
	);
}

void	draw_ft120(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		pixel_info
	);
}

void	draw_ft201(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		pixel_info
	);
}

void	draw_ft210(t_pixel_info *pixel_info, int i)
{
	draw_filled_triangle(
		&((*((*(*pixel_info).scene).projected_triangle + i))).p2,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p1,
		&((*((*(*pixel_info).scene).projected_triangle + i))).p0,
		pixel_info
	);
}
