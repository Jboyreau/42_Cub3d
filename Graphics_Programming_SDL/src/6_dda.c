#include "header.h"

void	y_minus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda)
{
	int i = -1;
	int y = (*dda).p1.y;
	int x = (*dda).p1.x;

	while (++i < (*dda).abs_delta_x)
	{
		(*pixel_info).cell = x + (y << 10) + (y << 8);
		(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
		--x;
	}
}

void	y_plus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda)
{
	int i = -1;
	int y = (*dda).p1.y;
	int x = (*dda).p1.x;

	while (++i < (*dda).abs_delta_x)
	{
		(*pixel_info).cell = x + (y << 10) + (y << 8);
		(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
		++x;
	}
}

void	x_minus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda)
{
	int i = -1;
	int y = (*dda).p1.y;
	int x = (*dda).p1.x;

	while (++i < (*dda).abs_delta_y)
	{
		(*pixel_info).cell = x + (y << 10) + (y << 8);
		(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
		--y;
	}
}

void	x_plus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda)
{
	int i = -1;
	int y = (*dda).p1.y;
	int x = (*dda).p1.x;

	while (++i < (*dda).abs_delta_y)
	{
		(*pixel_info).cell = x + (y << 10) + (y << 8);
		(*(*scene).fun).fun_draw_pixel[((*pixel_info).cell > 0 && (*pixel_info).cell < BUFF_SIZE)](pixel_info);
		++y;
	}
}

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
	char	abs_delta_positive;
	char	dx_more_than_dy;
	char	dy_null_dx_not;
	char	dx_null_dy_not;

	dda.p1 = (*((*scene).projected_triangle + i)).a;
	dda.p2 = (*((*scene).projected_triangle + i)).b;
	dda.delta_x = dda.p2.x - dda.p1.x;
	dda.delta_y = dda.p2.y - dda.p1.y;
	dda.abs_delta_x = abs(dda.delta_x);
	dda.abs_delta_y = abs(dda.delta_y);
	abs_delta_positive = (dda.abs_delta_x && dda.abs_delta_y);
	dx_more_than_dy = (dda.abs_delta_x >= dda.abs_delta_y);
	dy_null_dx_not = (dda.abs_delta_y == 0 && dda.abs_delta_x);
	dx_null_dy_not = (dda.abs_delta_x == 0 && dda.abs_delta_y);
	(*(*scene).fun).dda[
		(abs_delta_positive && dda.abs_delta_x < dda.abs_delta_y && dda.delta_y > 0)
		+ ((abs_delta_positive && (dx_more_than_dy && dda.delta_x < 0)) << 1)
		+ ((abs_delta_positive && (dx_more_than_dy && dda.delta_x > 0)) << 2)
		+ ((dy_null_dx_not && ((int)(dda.p1.x) > (int)(dda.p2.x))) << 3)
		+ ((dy_null_dx_not && ((int)(dda.p1.x) < (int)(dda.p2.x))) << 4)
		+ ((dx_null_dy_not && ((int)(dda.p1.y) > (int)(dda.p2.y))) << 5)
		+ ((dx_null_dy_not && ((int)(dda.p1.y) < (int)(dda.p2.y))) << 6)
	](scene, pixel_info, &dda);

	dda.p1 = (*((*scene).projected_triangle + i)).b;
	dda.p2 = (*((*scene).projected_triangle + i)).c;
	dda.delta_x = dda.p2.x - dda.p1.x;
	dda.delta_y = dda.p2.y - dda.p1.y;
	dda.abs_delta_x = abs(dda.delta_x);
	dda.abs_delta_y = abs(dda.delta_y);
	abs_delta_positive = (dda.abs_delta_x && dda.abs_delta_y);
	dx_more_than_dy = (dda.abs_delta_x >= dda.abs_delta_y);
	dy_null_dx_not = (dda.abs_delta_y == 0 && dda.abs_delta_x);
	dx_null_dy_not = (dda.abs_delta_x == 0 && dda.abs_delta_y);
	(*(*scene).fun).dda[
		(abs_delta_positive && dda.abs_delta_x < dda.abs_delta_y && dda.delta_y > 0)
		+ ((abs_delta_positive && (dx_more_than_dy && dda.delta_x < 0)) << 1)
		+ ((abs_delta_positive && (dx_more_than_dy && dda.delta_x > 0)) << 2)
		+ ((dy_null_dx_not && ((int)(dda.p1.x) > (int)(dda.p2.x))) << 3)
		+ ((dy_null_dx_not && ((int)(dda.p1.x) < (int)(dda.p2.x))) << 4)
		+ ((dx_null_dy_not && ((int)(dda.p1.y) > (int)(dda.p2.y))) << 5)
		+ ((dx_null_dy_not && ((int)(dda.p1.y) < (int)(dda.p2.y))) << 6)
	](scene, pixel_info, &dda);


	dda.p1 = (*((*scene).projected_triangle + i)).c;
	dda.p2 = (*((*scene).projected_triangle + i)).a;
	dda.delta_x = dda.p2.x - dda.p1.x;
	dda.delta_y = dda.p2.y - dda.p1.y;
	dda.abs_delta_x = abs(dda.delta_x);
	dda.abs_delta_y = abs(dda.delta_y);
	abs_delta_positive = (dda.abs_delta_x && dda.abs_delta_y);
	dx_more_than_dy = (dda.abs_delta_x >= dda.abs_delta_y);
	dy_null_dx_not = (dda.abs_delta_y == 0 && dda.abs_delta_x);
	dx_null_dy_not = (dda.abs_delta_x == 0 && dda.abs_delta_y);
	(*(*scene).fun).dda[
		(abs_delta_positive && dda.abs_delta_x < dda.abs_delta_y && dda.delta_y > 0)
		+ ((abs_delta_positive && (dx_more_than_dy && dda.delta_x < 0)) << 1)
		+ ((abs_delta_positive && (dx_more_than_dy && dda.delta_x > 0)) << 2)
		+ ((dy_null_dx_not && ((int)(dda.p1.x) > (int)(dda.p2.x))) << 3)
		+ ((dy_null_dx_not && ((int)(dda.p1.x) < (int)(dda.p2.x))) << 4)
		+ ((dx_null_dy_not && ((int)(dda.p1.y) > (int)(dda.p2.y))) << 5)
		+ ((dx_null_dy_not && ((int)(dda.p1.y) < (int)(dda.p2.y))) << 6)
	](scene, pixel_info, &dda);

}
