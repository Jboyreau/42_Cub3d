#include "header.h"

void	poly_to_tri(t_scene *scene, t_v3 *poly, t_tri *face)
{
	int	i;

	(*scene).nb_tri = 0;
	i = -1;
	while (++i < (*scene).poly_size - 2)
	{
		(*((*scene).projected_triangle + (*scene).nb_tri)).a = *poly;
		(*((*scene).projected_triangle + (*scene).nb_tri)).p0.uv = (*face).uv_a;
		(*((*scene).projected_triangle + (*scene).nb_tri)).b = *(poly + i + 1);
		(*((*scene).projected_triangle + (*scene).nb_tri)).p1.uv = (*face).uv_b;
		(*((*scene).projected_triangle + (*scene).nb_tri)).c = *(poly + i + 2);
		(*((*scene).projected_triangle + (*scene).nb_tri)).p2.uv = (*face).uv_c;
		++(*scene).nb_tri;
	}
	i = -1;
	while (++i < (*scene).poly_size)
	{
		*(poly + i) = (*scene).origin;
		(*((*scene).inside_vertices + i)) = (*scene).origin;
	}
}

void	inter_p_outside(t_scene *scene, t_line *cp, t_v2 *dot, t_v3 *inside_vertices)
{
	float	t;
	t_v3	q12;

	t = ((*dot).x / ((*dot).x - (*dot).y));
	q12 = vec3_subtract((*cp).cur, (*cp).prev);
	q12 = vec3_multiplication(&q12, t);
	*(inside_vertices + (*scene).inside_size) = vec3_addition((*cp).prev, &q12);
	*(inside_vertices + (*scene).inside_size + 1) = *((*cp).cur);
	(*scene).inside_size += 2;
//	printf("\tprev out\n");
}

void	inter_c_outside(t_scene *scene, t_line *cp, t_v2 *dot, t_v3 *inside_vertices)
{
	float	t;
	t_v3	q12;

	t = ((*dot).x / ((*dot).x - (*dot).y));
	q12 = vec3_subtract((*cp).cur, (*cp).prev);
	q12 = vec3_multiplication(&q12, t);
	*(inside_vertices + (*scene).inside_size) = vec3_addition((*cp).prev, &q12);
	++(*scene).inside_size;
//	printf("\tcur out\n");
}

void	inter_both_inside(t_scene *scene, t_line *cp, t_v2 *dot, t_v3 *inside_vertices)
{
	(void)dot;
	*(inside_vertices + (*scene).inside_size) = *((*cp).cur);
	++(*scene).inside_size;
//	printf("\tinside\n");
}

void	inter_both_outside(t_scene *scene, t_line *cp, t_v2 *dot, t_v3 *inside_vertices)
{
	(void)scene;
	(void)cp;
	(void)dot;
	(void)inside_vertices;
//	printf("\tboth out\n");
}

static	void	clip(t_scene *scene, t_plane *plane, t_v3 **poly, t_v3 **ins_vert)
{
	t_line		cp;
	t_v2		dot;
	t_v3		*temp;

	cp.cur = *poly;
	cp.prev = *poly + (*scene).poly_size - 1;
	cp.vec_cur = vec3_subtract(cp.cur, &((*plane).point));
	cp.vec_prev = vec3_subtract(cp.prev, &((*plane).point));
	dot.x = vec3_dot(&(cp.vec_prev), &((*plane).n));
	(*scene).inside_size = 0;
	while (cp.cur != (*poly) + (*scene).poly_size)
	{
		cp.vec_cur = vec3_subtract(cp.cur, &((*plane).point));
		dot.y = vec3_dot(&(cp.vec_cur), &((*plane).n));
		//printf("\t\tdot.cur = %f\n", dot.y);
		//printf("\t\tdot.prev = %f\n", dot.x);
		(*(*scene).fun).inter[
			(dot.y >= 0 && dot.x < 0) //p out
			+ ((dot.x >= 0 && dot.y < 0) << 1) //c out
			+ ((dot.y >= 0 && dot.x >= 0) << 2) // both inside
		](scene, &cp, &dot, *ins_vert);
		dot.x = dot.y;
		cp.prev = cp.cur;
		++(cp.cur);
	}
	(*scene).poly_size = (*scene).inside_size;
	temp = *poly;
	*poly = *ins_vert;
	*ins_vert = temp;
}

t_v3	*tri_to_poly(t_scene *scene, t_tri *face)
{
	t_v3 *pt_poly;
	t_v3 *pt_ins_vert;

	pt_poly = (*scene).poly;
	pt_ins_vert = (*scene).inside_vertices;
	(*(*scene).poly) = *((*scene).cloud + (*face).a);
	(*((*scene).poly + 1)) = *((*scene).cloud + (*face).b);
	(*((*scene).poly + 2)) = *((*scene).cloud + (*face).c);
	(*scene).poly_size = 3;
//	printf("-------NEAR-------\n");
	clip(scene, &((*scene).view.near), &pt_poly, &pt_ins_vert);
//	printf("-------FAR-------\n");
	clip(scene, &((*scene).view.far), &pt_poly, &pt_ins_vert);
//	printf("-------LEFT-------\n");
	clip(scene, &((*scene).view.left), &pt_poly, &pt_ins_vert);
//	printf("-------RIGHT-------\n");
	clip(scene, &((*scene).view.right), &pt_poly, &pt_ins_vert);
//	printf("-------TOP-------\n");
	clip(scene, &((*scene).view.top), &pt_poly, &pt_ins_vert);
//	printf("-------BOTTOM-------\n");
	clip(scene, &((*scene).view.bottom), &pt_poly, &pt_ins_vert);
	//printf("poly_size = %d, inside_size = %d\n----------------------\n", (*scene).poly_size, (*scene).inside_size);
	return ((*scene).poly);
}
