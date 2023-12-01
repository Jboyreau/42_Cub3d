#include "header.h"

static t_v3	init_face(t_v2 *a, float az)
{
	t_v3	p;

	p.x = (*a).x;
	p.y = (*a).y;
	p.z = az;
	return (p);
}

static t_v3	calcultate_interpolated_normal(t_pixel_info *pixel_info)
{
	t_v3	int_normal;

	int_normal.x = (*pixel_info).weight.x * (*pixel_info).p0.normal.x + (*pixel_info).weight.y * (*pixel_info).p1.normal.x + (*pixel_info).weight.z * (*pixel_info).p2.normal.x;
	int_normal.y = (*pixel_info).weight.x * (*pixel_info).p0.normal.y + (*pixel_info).weight.y * (*pixel_info).p1.normal.y + (*pixel_info).weight.z * (*pixel_info).p2.normal.y;
	int_normal.z = (*pixel_info).weight.x * (*pixel_info).p0.normal.z + (*pixel_info).weight.y * (*pixel_info).p1.normal.z + (*pixel_info).weight.z * (*pixel_info).p2.normal.z;
	return (int_normal);
}

void	dot(t_pixel_info *pixel_info)
{
	t_v3	p;
	t_v3	normal;
	t_v3	camera_ray;

	p = init_face(&(*pixel_info).p, (*pixel_info).interpolated.w);
	normal = calcultate_interpolated_normal(pixel_info);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*pixel_info).screen_space_origin), &p);
	vec3_normalize(&camera_ray);
	(*pixel_info).dot = vec3_dot(&camera_ray, &normal);
	if ((*pixel_info).dot < 0 || isnanf((*pixel_info).dot) || isinf((*pixel_info).dot) || (*pixel_info).dot > 1)
		(*pixel_info).dot = 0;
}

static int	find_color(t_pixel_info *pixel_info)
{
	int 	cell;

	(*pixel_info).interpolated.u = ((*pixel_info).weight.x * (*pixel_info).p0_itu
	+ (*pixel_info).weight.y * (*pixel_info).p1_itu
	+ (*pixel_info).weight.z * (*pixel_info).p2_itu) * (*pixel_info).interpolated.w;
	(*pixel_info).interpolated.v = ((*pixel_info).weight.x * (*pixel_info).p0_itv
	+ (*pixel_info).weight.y * (*pixel_info).p1_itv
	+ (*pixel_info).weight.z * (*pixel_info).p2_itv) * (*pixel_info).interpolated.w;
	cell = *((*(*pixel_info).scene).tex_w + (*pixel_info).texture) * ((int)((*pixel_info).interpolated.v * (*((*(*pixel_info).scene).tex_h + (*pixel_info).texture))) + (*pixel_info).interpolated.u);
	cell *= (cell > 0 && cell < *((*(*pixel_info).scene).t_size + (*pixel_info).texture));
	return (*(*((*(*pixel_info).scene).texture + (*pixel_info).texture) + cell));
}

void blend_color(t_pixel_info *pixel_info)
{
 // Ajouter une couleur de brouillard grise en fonction de la distance
    double fog_factor = 1.0 - exp(-0.08 * (*pixel_info).interpolated.w); // Fonction linéaire simple (ajustez si nécessaire)

    // Couleur du brouillard grise (par exemple, un gris moyen)
    int fog_color = FOG;

    // Extraire les composants de couleur
    int original_r = (*pixel_info).color >> 16 & 0xFF;
    int original_g = (*pixel_info).color >> 8 & 0xFF;
    int original_b = (*pixel_info).color & 0xFF;

    int blended_r = (1.0 - fog_factor) * original_r + fog_factor * ((fog_color >> 16 & 0xFF) * (*pixel_info).dot);
    int blended_g = (1.0 - fog_factor) * original_g + fog_factor * ((fog_color >> 8 & 0xFF) * (*pixel_info).dot);
    int blended_b = (1.0 - fog_factor) * original_b + fog_factor * ((fog_color & 0xFF) * (*pixel_info).dot);

    // Combinez les composants de couleur mélangés
    int blended_color = 0xFF000000 | (blended_r << 16) | (blended_g << 8) | blended_b; 
    (*pixel_info).color = blended_color;
}

void	draw_pixel(t_pixel_info *pixel_info)
{
	int a;
	int r;
	int g;
	int b;

	if ((*pixel_info).interpolated.w < 60)
	{
		dot(pixel_info);
		(*pixel_info).color = find_color(pixel_info);
	//	blend_color(pixel_info);
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
		return ;
	}
	(*pixel_info).color = 0xff404040;//find_color(pixel_info);
	//	blend_color(pixel_info);
	a = 0xFF000000;
	r = ((*pixel_info).color & 0x00FF0000) * (*(*pixel_info).scene).dot;
	g = ((*pixel_info).color & 0x0000FF00) * (*(*pixel_info).scene).dot;
	b = ((*pixel_info).color & 0x000000FF) * (*(*pixel_info).scene).dot;
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
