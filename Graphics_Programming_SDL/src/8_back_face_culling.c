#include "header.h"

float is_visible(t_scene *scene, int i)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	normal;
	t_v3	camera_ray;

	face = *((*scene).projected_triangle + i);
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vec3_normalize(&vecAB);
	vecAC = vec3_subtract(&(face.c), &(face.a));
	vec3_normalize(&vecAC);
	normal = vec3_cross(&vecAB, &vecAC);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*scene).origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*scene).dot = vec3_dot(&camera_ray, &normal);
	//printf("%f\n", (*scene).dot);
	return ((*scene).dot);
}
