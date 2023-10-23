#include "header.h"
#define ONE_HALF 0.5

void	dda_x_minus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda)
{
	float	y_inc;
	float	current_y;
	int		current_x;
	int		y;
	int		i;

	y_inc = (*dda).delta_y / (float)(*dda).abs_delta_x;
	current_x = (*dda).p1.x;
	current_y = (*dda).p1.y;
	i = -1;
	while (++i <= (*dda).abs_delta_x)
	{
		y = round(current_y);
		(*pixel_info).cell = current_x + (y << 10) + (y << 8);
		(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
		--current_x;
		current_y += y_inc;
	}
}

void	dda_x_plus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda)
{
	float	y_inc;
	float	current_y;
	int		current_x;
	int		y;
	int		i;

	y_inc = (*dda).delta_y / (float)(*dda).abs_delta_x;
	current_x = (*dda).p1.x;
	current_y = (*dda).p1.y;
	i = -1;
	while (++i <= (*dda).abs_delta_x)
	{
		y = round(current_y);
		(*pixel_info).cell = current_x + (y << 10) + (y << 8);
		(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
		++current_x;
		current_y += y_inc;
	}
}

void	dda_y_minus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda)
{
	float	x_inc;
	float	current_x;
	int		current_y;
	int		i;

	x_inc = (*dda).delta_x / (float)(*dda).abs_delta_y;
	current_x = (*dda).p1.x;
	current_y = (*dda).p1.y;
	i = -1;
	while (++i <= (*dda).abs_delta_y)
	{
		(*pixel_info).cell = (int)round(current_x) + (current_y << 10) + (current_y << 8);
		(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
		current_x += x_inc;
		--current_y;
	}
}

void	dda_y_plus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda)
{
	float	x_inc;
	float	current_x;
	int		current_y;
	int		i;

	x_inc = (*dda).delta_x / (float)(*dda).abs_delta_y;
	current_x = (*dda).p1.x;
	current_y = (*dda).p1.y;
	i = -1;
	while (++i <= (*dda).abs_delta_y)
	{
		(*pixel_info).cell = (int)round(current_x) + (current_y << 10) + (current_y << 8);
		(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
		current_x += x_inc;
		++current_y;
	}
}

void	draw_triangle(t_scene *scene, t_pixel_info *pixel_info, int i)
{
	t_dda	dda;

	dda.p1 = (*((*scene).projected_triangle + i)).a;
	dda.p2 = (*((*scene).projected_triangle + i)).b;
	dda.delta_x = dda.p2.x - dda.p1.x;
	dda.delta_y = dda.p2.y - dda.p1.y;
	dda.abs_delta_x = abs(dda.delta_x);
	dda.abs_delta_y = abs(dda.delta_y);
	(*(*scene).fun).dda[
		(dda.abs_delta_x < dda.abs_delta_y && dda.delta_y > 0)
		+ ((dda.abs_delta_x >= dda.abs_delta_y && dda.delta_x < 0) << 1)
		+ ((dda.abs_delta_x >= dda.abs_delta_y && dda.delta_x > 0) << 2)
	](scene, pixel_info, &dda);

	dda.p1 = (*((*scene).projected_triangle + i)).b;
	dda.p2 = (*((*scene).projected_triangle + i)).c;
	dda.delta_x = dda.p2.x - dda.p1.x;
	dda.delta_y = dda.p2.y - dda.p1.y;
	dda.abs_delta_x = abs(dda.delta_x);
	dda.abs_delta_y = abs(dda.delta_y);
	(*(*scene).fun).dda[
		(dda.abs_delta_x < dda.abs_delta_y && dda.delta_y > 0)
		+ ((dda.abs_delta_x >= dda.abs_delta_y && dda.delta_x < 0) << 1)
		+ ((dda.abs_delta_x >= dda.abs_delta_y && dda.delta_x > 0) << 2)
	](scene, pixel_info, &dda);

	dda.p1 = (*((*scene).projected_triangle + i)).c;
	dda.p2 = (*((*scene).projected_triangle + i)).a;
	dda.delta_x = dda.p2.x - dda.p1.x;
	dda.delta_y = dda.p2.y - dda.p1.y;
	dda.abs_delta_x = abs(dda.delta_x);
	dda.abs_delta_y = abs(dda.delta_y);
	(*(*scene).fun).dda[
		(dda.abs_delta_x < dda.abs_delta_y && dda.delta_y > 0)
		+ ((dda.abs_delta_x >= dda.abs_delta_y && dda.delta_x < 0) << 1)
		+ ((dda.abs_delta_x >= dda.abs_delta_y && dda.delta_x > 0) << 2)
	](scene, pixel_info, &dda);
}
