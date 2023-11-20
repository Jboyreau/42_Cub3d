#include "header.h"

static int	find_color(t_v3 *weight, t_pixel_info *pixel_info)
{
	t_tex3	interpolated;
	int 	cell;

	interpolated.w = 1 / ((*weight).x * (*pixel_info).p0.inv_z + (*weight).y * (*pixel_info).p1.inv_z + (*weight).z * (*pixel_info).p2.inv_z);
	(*pixel_info).depth = interpolated.w;
	interpolated.u = ((*weight).x * (*pixel_info).p0_itu
	+ (*weight).y * (*pixel_info).p1_itu
	+ (*weight).z * (*pixel_info).p2_itu) * interpolated.w;
	interpolated.v = ((*weight).x * (*pixel_info).p0_itv
	+ (*weight).y * (*pixel_info).p1_itv
	+ (*weight).z * (*pixel_info).p2_itv) * interpolated.w;
	cell = (*(*pixel_info).scene).tex_w * ((int)(interpolated.v * (*(*pixel_info).scene).tex_h) + interpolated.u);
//pthread_mutex_lock((*(*pixel_info).scene).mutex_buffer);
	cell *= (cell > -1 && cell < (*(*pixel_info).scene).t_size);
//pthread_mutex_unlock((*(*pixel_info).scene).mutex_buffer);
	return (*((*(*pixel_info).scene).texture + cell));
}

static t_v3	*barycentric_weight(t_pixel_info* pixel_info)
{
	static t_v3	weight;
	t_br		ref;

	ref.ap = vec2_subtract(&(*pixel_info).p, &(*pixel_info).a);
	ref.pc = vec2_subtract(&(*pixel_info).c, &(*pixel_info).p);
	ref.pb = vec2_subtract(&(*pixel_info).b, &(*pixel_info).p);
	weight.x = (ref.pc.x * ref.pb.y - ref.pc.y * ref.pb.x) * (*pixel_info).para_abc;
	weight.y = ((*pixel_info).ac.x * ref.ap.y - (*pixel_info).ac.y * ref.ap.x) * (*pixel_info).para_abc;
	weight.z = 1 - weight.x - weight.y;
	return (&weight);
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
	while (x_start <= x_end)
	{
		(*pixel_info).cell = x_start + y;
		(*pixel_info).p.x = x_start;
		(*pixel_info).color = find_color(barycentric_weight(pixel_info), pixel_info);
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			(*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) > (*pixel_info).depth)
		](pixel_info);
		++x_start;
	}
}

static void	draw_line2(int x_start, int x_end, int y, t_pixel_info *pixel_info)
{
	(*pixel_info).p.y = (*pixel_info).y;
	while (x_end <= x_start)
	{
		(*pixel_info).cell = x_end + y;
		(*pixel_info).p.x = x_end;
		(*pixel_info).color = find_color(barycentric_weight(pixel_info), pixel_info);
		(*(*(*pixel_info).scene).fun).fun_draw_pixel[
			(*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) > (*pixel_info).depth)
		](pixel_info);
		++x_end;
	}
}

static void	fill_flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1)
{
	float	inv_sloap_1;
	float	x_start;
	float	x_end;
	int		y;

	inv_sloap_1 = ((*p1).x - (*p0).x) / (float)((*p1).y - (*p0).y);
	
	x_start = (*p0).x + ((*pixel_info).y_start - (*p0).y) * inv_sloap_1;
	x_end = (*p0).x + ((*pixel_info).y_start - (*p0).y) * (*pixel_info).inv_sloap_2;
	y = (*pixel_info).y_start;
	while (y <= (*pixel_info).y_end && (y <= (*p1).y && (*p0).y != (*p1).y))
	{
		(*pixel_info).y = y;
		if (x_start < x_end)
			draw_line(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end += (*pixel_info).inv_sloap_2;
		++y;
	}/*
if ((*p0).y != (*p1).y)
{
	pthread_mutex_lock((*(*pixel_info).scene).code_mutex + INTER_THREAD);
	printf("BOTTOM : y_s = %d, y_e = %d, p0(%d, %d); p1(%d, %d)\n", (int)(*pixel_info).y_start, (int)(*pixel_info).y_end, (*p0).x, (*p0).y, (*p1).x, (*p1).y);
	pthread_mutex_unlock((*(*pixel_info).scene).code_mutex + INTER_THREAD);
}*/
}

static void	fill_flat_top(t_pixel_info *pixel_info, t_point *p2, t_point *p1)
{
	float	inv_sloap_1;
	float	x_start;
	float	x_end;
	int		y;
	
	inv_sloap_1 = ((*p1).x - (*p2).x) / (float)((*p2).y - (*p1).y);
	
	x_start = (*p2).x + ((*p2).y - (*pixel_info).y_start) * inv_sloap_1;
	x_end = (*p2).x - ((*p2).y - ((*pixel_info).y_start)) * (*pixel_info).inv_sloap_2;
	y = (*pixel_info).y_start;
	while (y >= (*pixel_info).y_end && (y >= (*p1).y && (*p2).y != (*p1).y))
	{
		(*pixel_info).y = y;
		if (x_start < x_end)
			draw_line(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		else
			draw_line2(x_start, x_end, ((y << 10) + (y << 8)), pixel_info);
		x_start += inv_sloap_1;
		x_end -= (*pixel_info).inv_sloap_2;
		--y;
	}/*
if ((*p2).y != (*p1).y)
{
	pthread_mutex_lock((*(*pixel_info).scene).code_mutex + INTER_THREAD);
	printf("\tTOP : y_s = %d, y_e = %d, p1(%d, %d); p2(%d, %d)\n", (int)(*pixel_info).y_start, (int)(*pixel_info).y_end, (*p1).x, (*p1).y, (*p2).x, (*p2).y);
	pthread_mutex_unlock((*(*pixel_info).scene).code_mutex + INTER_THREAD);
}*/
}

void	flat_bottom_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index)
{	
	(*pixel_info).inv_sloap_2 = ((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y);
	
	(*pixel_info).len_y = (*pixel_info).p1.y - (*pixel_info).p0.y;
	(*pixel_info).ratio = (*pixel_info).len_y / THREAD_NUM;
	(*pixel_info).ratio += ((*pixel_info).ratio == 0);
	(*pixel_info).modulo = (*pixel_info).len_y % THREAD_NUM;
	(*pixel_info).y_start = (*p0).y + (thread_index * (*pixel_info).ratio);
	if ((thread_index == THREAD_NUM - 1) && (*pixel_info).modulo != 0 && (*pixel_info).ratio > 0)
		(*pixel_info).y_end = (*pixel_info).y_start + (*pixel_info).ratio + (*pixel_info).modulo;
	else
		(*pixel_info).y_end = (*pixel_info).y_start + (*pixel_info).ratio;
	(*pixel_info).y_start += (thread_index > 0);
//	pthread_mutex_lock((*(*pixel_info).scene).code_mutex + INTER_THREAD);
//	printf("len = %d, ratio = %d, thread_index = %d\n", (*pixel_info).len_y, (*pixel_info).ratio, thread_index);
//	pthread_mutex_unlock((*(*pixel_info).scene).code_mutex + INTER_THREAD);
	fill_flat_bottom(pixel_info, p0, p1);
	
	(*pixel_info).len_y = (*pixel_info).p2.y - (*pixel_info).p1.y;
	(*pixel_info).ratio = (*pixel_info).len_y / THREAD_NUM;
	(*pixel_info).ratio += ((*pixel_info).ratio == 0);
	(*pixel_info).modulo = (*pixel_info).len_y % THREAD_NUM;
	(*pixel_info).y_start = (*p2).y - (thread_index * (*pixel_info).ratio);
	if ((thread_index == THREAD_NUM - 1) && (*pixel_info).modulo != 0 && (*pixel_info).ratio > 0)
		(*pixel_info).y_end = (*pixel_info).y_start - (*pixel_info).ratio - (*pixel_info).modulo;
	else
		(*pixel_info).y_end = (*pixel_info).y_start - (*pixel_info).ratio;
	(*pixel_info).y_start += (thread_index > 0);
//	pthread_mutex_lock((*(*pixel_info).scene).code_mutex + INTER_THREAD);
//	printf("len = %d, ratio = %d, thread_index = %d\n", (*pixel_info).len_y, (*pixel_info).ratio, thread_index);
//	pthread_mutex_unlock((*(*pixel_info).scene).code_mutex + INTER_THREAD);	
	fill_flat_top(pixel_info, p2, p1);
}


void	nothing_tb(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index)
{
	(void)pixel_info;
	(void)p0;
	(void)p1;
	(void)p2;
	(void)thread_index;
}

void	flat_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index)
{
	(*pixel_info).inv_sloap_2 = ((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y);
	
	(*pixel_info).len_y = (*pixel_info).p2.y - (*pixel_info).p0.y;
	(*pixel_info).ratio = (*pixel_info).len_y / THREAD_NUM;
	(*pixel_info).ratio += ((*pixel_info).ratio == 0);
	(*pixel_info).modulo = (*pixel_info).len_y % THREAD_NUM;
	(*pixel_info).y_start = (*p2).y - (thread_index * (*pixel_info).ratio);
	if ((thread_index == THREAD_NUM - 1) && (*pixel_info).modulo != 0 && (*pixel_info).ratio > 0)
		(*pixel_info).y_end = (*pixel_info).y_start - (*pixel_info).ratio - (*pixel_info).modulo;
	else
		(*pixel_info).y_end = (*pixel_info).y_start - (*pixel_info).ratio;
	(*pixel_info).y_start += (thread_index > 0);
	
	fill_flat_top(pixel_info, p2, p1);
}

void	flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index)
{
	(*pixel_info).inv_sloap_2 = ((*p0).x - (*p2).x) / (float)((*p0).y - (*p2).y);
	
	(*pixel_info).len_y = (*pixel_info).p2.y - (*pixel_info).p0.y;
	(*pixel_info).ratio = (*pixel_info).len_y / THREAD_NUM;
	(*pixel_info).ratio += ((*pixel_info).ratio == 0);
	(*pixel_info).modulo = (*pixel_info).len_y % THREAD_NUM;
	(*pixel_info).y_start = (*p0).y + (thread_index * (*pixel_info).ratio);
	if ((thread_index == THREAD_NUM - 1) && (*pixel_info).modulo != 0 && (*pixel_info).ratio > 0)
		(*pixel_info).y_end = (*pixel_info).y_start + (*pixel_info).ratio + (*pixel_info).modulo;
	else
		(*pixel_info).y_end = (*pixel_info).y_start + (*pixel_info).ratio;
	(*pixel_info).y_start += (thread_index > 0);
	
	fill_flat_bottom(pixel_info, p0, p1);
}

/* ROUTINE----------------------------------------------------------------*/

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
	while ((*pixel_info.scene).ret)
	{
		pthread_barrier_wait((*(t_arg *)arg).pixel_info.first_wall);
		pixel_info = (*(t_arg *)arg).pixel_info;
//	pthread_mutex_lock((*pixel_info.scene).code_mutex);
//	printf("-----THREAD: %d------\n", thread_index);
		(*(*pixel_info.scene).fun).flat_top_or_bottom[
		pixel_info.condition
		](&pixel_info, &pixel_info.p0, &pixel_info.p1, &pixel_info.p2, thread_index);
//	pthread_mutex_unlock((*pixel_info.scene).code_mutex);
		pthread_barrier_wait((*(t_arg *)arg).pixel_info.wait_triangle);
	}
	return (NULL);
}
/* ROUTINE----------------------------------------------------------------*/

static void	call_thread(t_pixel_info *pixel_info)
{
	
	pthread_barrier_wait((*pixel_info).first_wall);
	pthread_barrier_wait((*pixel_info).wait_triangle);
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
	interpolated_uv_init(pixel_info);
	(*pixel_info).condition = ((*p1).y == (*p0).y && ((*p1).y != (*p0).y)) 
	+ (((*p1).y == (*p2).y && ((*p1).y != (*p0).y)) << 1)
	+ ((((*p1).y == (*p0).y && (*p0).y == (*p2).y) || ((*p1).x == (*p0).x && (*p0).x == (*p2).x)) << 2);
/*
pthread_mutex_lock((*(*pixel_info).scene).code_mutex);
printf("\n#############-----TRI------#############\n");
pthread_mutex_unlock((*(*pixel_info).scene).code_mutex);
*/
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
