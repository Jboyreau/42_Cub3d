#include "header.h"

t_ptri	init_face(t_v2 *a, float az, t_point *pb, t_point *pc)
{
	t_ptri	face;

	face.a.x = (*a).x;
	face.a.y = (*a).y;
	face.a.z = az;
	face.b.x = (*pb).x;
	face.b.y = (*pb).y;
	face.b.z = (*pb).z;
	face.c.x = (*pc).x;
	face.c.y = (*pc).y;
	face.c.z = (*pc).z;
	return (face);
}
/*
static void	dot_p02(t_pixel_info *pixel_info)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	normal;
	t_v3	camera_ray;

	face = init_face(&(*pixel_info).p, (*pixel_info).interpolated.w, &(*pixel_info).screen_space_p0, &(*pixel_info).screen_space_p1);
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vecAC = vec3_subtract(&(face.c), &(face.a));
	normal = vec3_cross(&vecAB, &vecAC);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*pixel_info).screen_space_origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*pixel_info).dot = vec3_dot(&camera_ray, &normal);
		if ((*pixel_info).dot < 0)
			printf("fatality\n");
}

static void	dot_p01(t_pixel_info *pixel_info)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	normal;
	t_v3	camera_ray;

	face = init_face(&(*pixel_info).p, (*pixel_info).interpolated.w, &(*pixel_info).screen_space_p0, &(*pixel_info).screen_space_p1);
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vecAC = vec3_subtract(&(face.c), &(face.a));
	normal = vec3_cross(&vecAB, &vecAC);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*pixel_info).screen_space_origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*pixel_info).dot = vec3_dot(&camera_ray, &normal);
		if ((*pixel_info).dot <= 0)
			dot_p02(pixel_info);
}

static void	dot_p10(t_pixel_info *pixel_info)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	normal;
	t_v3	camera_ray;

	face = init_face(&(*pixel_info).p, (*pixel_info).interpolated.w, &(*pixel_info).screen_space_p1, &(*pixel_info).screen_space_p0);
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vecAC = vec3_subtract(&(face.c), &(face.a));
	normal = vec3_cross(&vecAB, &vecAC);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*pixel_info).screen_space_origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*pixel_info).dot = vec3_dot(&camera_ray, &normal);
		if ((*pixel_info).dot < 0)
			dot_p01(pixel_info);
}

static void	dot_p12(t_pixel_info *pixel_info)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	normal;
	t_v3	camera_ray;

	face = init_face(&(*pixel_info).p, (*pixel_info).interpolated.w, &(*pixel_info).screen_space_p1, &(*pixel_info).screen_space_p2);
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vecAC = vec3_subtract(&(face.c), &(face.a));
	normal = vec3_cross(&vecAB, &vecAC);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*pixel_info).screen_space_origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*pixel_info).dot = vec3_dot(&camera_ray, &normal);
	if ((*pixel_info).dot < 0)
		dot_p10(pixel_info);
}

static void	dot_p21(t_pixel_info *pixel_info)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	normal;
	t_v3	camera_ray;

	face = init_face(&(*pixel_info).p, (*pixel_info).interpolated.w, &(*pixel_info).screen_space_p2, &(*pixel_info).screen_space_p1);
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vecAC = vec3_subtract(&(face.c), &(face.a));
	normal = vec3_cross(&vecAB, &vecAC);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*pixel_info).screen_space_origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*pixel_info).dot = vec3_dot(&camera_ray, &normal);
	if ((*pixel_info).dot < 0)
		dot_p12(pixel_info);
}
*/

void	dot_p20(t_pixel_info *pixel_info)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	normal;
	t_v3	camera_ray;

	face = init_face(&(*pixel_info).p, (*pixel_info).interpolated.w, &(*pixel_info).screen_space_p2, &(*pixel_info).screen_space_p0);
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vecAC = vec3_subtract(&(face.c), &(face.a));
	normal = vec3_cross(&vecAB, &vecAC);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*pixel_info).screen_space_origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*pixel_info).dot = vec3_dot(&camera_ray, &normal);
//	if ((*pixel_info).dot < 0)
//		dot_p21(pixel_info);
}
/*
static void calculate_dot(t_pixel_info *pixel_info)
{
	dot_p20(pixel_info);
}
*/
static int	find_color(t_pixel_info *pixel_info)
{
	int 	cell;

	(*pixel_info).interpolated.u = ((*pixel_info).weight.x * (*pixel_info).p0_itu
	+ (*pixel_info).weight.y * (*pixel_info).p1_itu
	+ (*pixel_info).weight.z * (*pixel_info).p2_itu) * (*pixel_info).interpolated.w;
	(*pixel_info).interpolated.v = ((*pixel_info).weight.x * (*pixel_info).p0_itv
	+ (*pixel_info).weight.y * (*pixel_info).p1_itv
	+ (*pixel_info).weight.z * (*pixel_info).p2_itv) * (*pixel_info).interpolated.w;
	cell = (*(*pixel_info).scene).tex_w * ((int)((*pixel_info).interpolated.v * (*(*pixel_info).scene).tex_h) + (*pixel_info).interpolated.u);
	cell *= (cell > -1 && cell < (*(*pixel_info).scene).t_size);
	return (*((*(*pixel_info).scene).texture + cell));
}

void	draw_pixel2(t_pixel_info *pixel_info)
{
	int a;
	int r;
	int g;
	int b;

	(*pixel_info).color = find_color(pixel_info);
	a = 0xFF000000;
	r = ((*pixel_info).color & 0x00FF0000) * (*pixel_info).dot;
	g = ((*pixel_info).color & 0x0000FF00) * (*pixel_info).dot;
	b = ((*pixel_info).color & 0x000000FF) * (*pixel_info).dot;
	*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) = (*pixel_info).interpolated.w;
	*((*(*pixel_info).scene).color_buffer + (*pixel_info).cell) = 
		a 
		| (r & 0x00FF0000)
		| (g & 0x0000FF00)
		| (b & 0x000000FF);
}

void	draw_pixel(t_pixel_info *pixel_info)
{
	int a;
	int r;
	int g;
	int b;

	dot_p20(pixel_info);
	(*pixel_info).color = find_color(pixel_info);
	//calculate_dot(pixel_info);
	a = 0xFF000000;
	r = ((*pixel_info).color & 0x00FF0000) * (*pixel_info).dot;
	g = ((*pixel_info).color & 0x0000FF00) * (*pixel_info).dot;
	b = ((*pixel_info).color & 0x000000FF) * (*pixel_info).dot;
	*((*(*pixel_info).scene).z_buffer + (*pixel_info).cell) = (*pixel_info).interpolated.w;
	*((*(*pixel_info).scene).color_buffer + (*pixel_info).cell) = 
		a 
		| (r & 0x00FF0000)
		| (g & 0x0000FF00)
		| (b & 0x000000FF);
}

void	do_not_draw_pixel(t_pixel_info *pixel_info)
{
	(void)pixel_info;
}
