#include "header.h"

static t_v3	barycentric_weight(t_pixel_info* pixel_info)
{
	t_v3	weight;
	t_br		ref;

	ref.ap = vec2_subtract(&(*pixel_info).p, &(*pixel_info).a);
	ref.pc = vec2_subtract(&(*pixel_info).c, &(*pixel_info).p);
	ref.pb = vec2_subtract(&(*pixel_info).b, &(*pixel_info).p);
	weight.x = (ref.pc.x * ref.pb.y - ref.pc.y * ref.pb.x) * (*pixel_info).para_abc;
	weight.y = ((*pixel_info).ac.x * ref.ap.y - (*pixel_info).ac.y * ref.ap.x) * (*pixel_info).para_abc;
	weight.z = 1 - weight.x - weight.y;
	return (weight);
}


static void	interpolated_uv_init(t_pixel_info *pixel_info)
{
	(*pixel_info).ac = vec2_subtract(&(*pixel_info).c, &(*pixel_info).a);
	(*pixel_info).ab = vec2_subtract(&(*pixel_info).b, &(*pixel_info).a);
	(*pixel_info).para_abc = 1 / (((*pixel_info).ac.x * (*pixel_info).ab.y) - ((*pixel_info).ac.y * (*pixel_info).ab.x));
	(*pixel_info).p0_itu = (*pixel_info).p0.uv.u * (*pixel_info).p0.inv_z;
	(*pixel_info).p1_itu = (*pixel_info).p1.uv.u * (*pixel_info).p1.inv_z;
	(*pixel_info).p2_itu = (*pixel_info).p2.uv.u * (*pixel_info).p2.inv_z;
	(*pixel_info).p0_itv = (*pixel_info).p0.uv.v * (*pixel_info).p0.inv_z;
	(*pixel_info).p1_itv = (*pixel_info).p1.uv.v * (*pixel_info).p1.inv_z;
	(*pixel_info).p2_itv = (*pixel_info).p2.uv.v * (*pixel_info).p2.inv_z;
}

static void	draw_line(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{
	(*pixel_info).p.y = (*pixel_info).y;
	while (x_start <= x_end && x_start >= 0 && x_start <= WIDTH)
	{
		(*pixel_info).cell = x_start + y;
		(*pixel_info).p.x = x_start;
		(*pixel_info).weight = barycentric_weight(pixel_info);
		(*pixel_info).interpolated.w = 1 / ((*pixel_info).weight.x * (*pixel_info).p0.inv_z + (*pixel_info).weight.y * (*pixel_info).p1.inv_z + (*pixel_info).weight.z * (*pixel_info).p2.inv_z);
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			(*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) > (*pixel_info).interpolated.w
			&& ((*pixel_info).weight.x >= 0 && (*pixel_info).weight.y >= 0
			&& (*pixel_info).weight.z >= 0
			&& ((*pixel_info).weight.x + (*pixel_info).weight.y + (*pixel_info).weight.z <= 1)))
		](pixel_info);
		++x_start;
	}
}

static void	draw_line2(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{
	(*pixel_info).p.y = (*pixel_info).y;
	while (x_end <= x_start && x_end >= 0 && x_end <= WIDTH)
	{
		(*pixel_info).cell = x_end + y;
		(*pixel_info).p.x = x_end;
		(*pixel_info).weight = barycentric_weight(pixel_info);
		(*pixel_info).interpolated.w = 1 / ((*pixel_info).weight.x * (*pixel_info).p0.inv_z + (*pixel_info).weight.y * (*pixel_info).p1.inv_z + (*pixel_info).weight.z * (*pixel_info).p2.inv_z);
		(*pixel_info).depth = (*pixel_info).interpolated.w;
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			(*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) > (*pixel_info).interpolated.w
			&& ((*pixel_info).weight.x >= 0 && (*pixel_info).weight.y >= 0
			&& (*pixel_info).weight.z >= 0
			&& ((*pixel_info).weight.x + (*pixel_info).weight.y + (*pixel_info).weight.z <= 1)))
		](pixel_info);
		++x_end;
	}
}

static void	fill_flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1, int thread_index)
{
	float	inv_sloap_1;
	float	x_start;
	float	x_end;
	int		y;

	inv_sloap_1 = (((*p1).x - (*p0).x) / (float)((*p1).y - (*p0).y));
	x_start = (*p0).x + thread_index * inv_sloap_1;
	x_end = (*p0).x + thread_index * (*pixel_info).inv_sloap_2;
	inv_sloap_1 *= (float)THREAD_NUM;
	y = (*pixel_info).y_start;
	while (y <= (*p1).y && y <= HEIGHT)
	{
		(*pixel_info).y = y;
		if (x_start < x_end)
			draw_line(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end += (*pixel_info).inv_sloap_2_factor;
		y += THREAD_NUM;
	}
}

static void	fill_flat_top(t_pixel_info *pixel_info, t_point *p2, t_point *p1, int thread_index)
{
	float	inv_sloap_1;
	float	x_start;
	float	x_end;
	int		y;
	
	inv_sloap_1 = (((*p1).x - (*p2).x) / (float)((*p2).y - (*p1).y));	
	x_start = (*p2).x + thread_index * inv_sloap_1;
	x_end = (*p2).x - thread_index * (*pixel_info).inv_sloap_2;
	inv_sloap_1 *= (float)THREAD_NUM;
	y = (*pixel_info).y_start;
	while (y >= (*p1).y && y >= 0)
	{
		(*pixel_info).y = y;
		if (x_start < x_end)
			draw_line(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end -= (*pixel_info).inv_sloap_2_factor;
		y -= THREAD_NUM;
	}
}

void	flat_bottom_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index)
{	
	(*pixel_info).inv_sloap_2 = (((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y));
	(*pixel_info).inv_sloap_2_factor = THREAD_NUM * (*pixel_info).inv_sloap_2;
	(*pixel_info).y_start = (*p0).y + thread_index;
	fill_flat_bottom(pixel_info, p0, p1, thread_index);
	(*pixel_info).y_start = (*p2).y - thread_index;
	fill_flat_top(pixel_info, p2, p1, thread_index);
}

void	flat_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index)
{
	(*pixel_info).inv_sloap_2 = (((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y));
	(*pixel_info).inv_sloap_2_factor = THREAD_NUM * (*pixel_info).inv_sloap_2;
	(*pixel_info).y_start = (*p2).y - thread_index;
	fill_flat_top(pixel_info, p2, p1, thread_index);
}

void	flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index)
{
	(*pixel_info).inv_sloap_2 = (((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y));
	(*pixel_info).inv_sloap_2_factor = THREAD_NUM * (*pixel_info).inv_sloap_2;
	(*pixel_info).y_start = (*p0).y + thread_index;
	fill_flat_bottom(pixel_info, p0, p1, thread_index);
}
void	nothing_tb(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index)
{
	(void)pixel_info;
	(void)p0;
	(void)p1;
	(void)p2;
	(void)thread_index;
}
/* ROUTINE----------------------------------------------------------------*/

void	wait_call(t_pixel_info *pixel_info)
{
	while ((*pixel_info).call < 1)
		;
}

void	notify_rdy(t_pixel_info *pixel_info)
{
	pthread_spin_lock((*pixel_info).fast_lock);
	++(*pixel_info).rdy;
	pthread_spin_unlock((*pixel_info).fast_lock);
	while ((*pixel_info).call)
		;
}

void	notify_finish(t_pixel_info *pixel_info)
{
	pthread_spin_lock((*pixel_info).fast_lock);
	++(*pixel_info).finish;
	pthread_spin_unlock((*pixel_info).fast_lock);
}

void	find_thread_index(pthread_t *thread, int *thread_index)
{
	pthread_t		id;
	
	*thread_index = 0;
	id = pthread_self();
	pthread_detach(id);
	while (pthread_equal(*( thread + *thread_index), id) == 0)
		++(*thread_index);
}

void	*start(void *arg)
{
	int				thread_index;
	t_pixel_info	pixel_info;

	pixel_info = (*(t_arg *)arg).pixel_info;
	find_thread_index((*pixel_info.scene).thread, &thread_index);
	while ((*(*(t_arg *)arg).pixel_info.scene).input != 3)
	{
		wait_call(&(*(t_arg *)arg).pixel_info);
		pixel_info = (*(t_arg *)arg).pixel_info;
		notify_rdy(&(*(t_arg *)arg).pixel_info);
		(*(*pixel_info.scene).fun).flat_top_or_bottom[
		pixel_info.condition
		](&pixel_info, &pixel_info.p0, &pixel_info.p1, &pixel_info.p2, thread_index);
		notify_finish(&(*(t_arg *)arg).pixel_info);
	}
	return (NULL);
}
/* ROUTINE----------------------------------------------------------------*/

static void	wait_rdy(t_pixel_info *pixel_info)
{
	while ((*pixel_info).rdy < THREAD_NUM)
		;
	(*pixel_info).call = 0;
}

static void	wait_finish(t_pixel_info *pixel_info)
{
	while ((*pixel_info).finish < THREAD_NUM)
		;
}

static void	call_thread(t_pixel_info *pixel_info)
{	
	(*pixel_info).rdy = 0;
	(*pixel_info).finish = 0;
	(*pixel_info).call = 1;
	wait_rdy(pixel_info);
	wait_finish(pixel_info);
}

static void	draw_filled_triangle(t_point *p0, t_point *p1, t_point *p2, t_pixel_info *pixel_info)
{
	(*pixel_info).a.x = (*p0).x;
	(*pixel_info).a.y = (*p0).y;
	(*pixel_info).b.x = (*p1).x;
	(*pixel_info).b.y = (*p1).y;
	(*pixel_info).c.x = (*p2).x;
	(*pixel_info).c.y = (*p2).y;
	(*pixel_info).p0 = (*p0);
	(*pixel_info).p1 = (*p1);
	(*pixel_info).p2 = (*p2);
	interpolated_uv_init(pixel_info);
	(*pixel_info).condition = ((*p1).y == (*p0).y && ((*p1).y != (*p0).y)) 
	+ (((*p1).y == (*p2).y && ((*p1).y != (*p0).y)) << 1);
	call_thread(pixel_info);
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
