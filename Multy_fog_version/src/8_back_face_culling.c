#include "header.h"

float is_visible(t_scene *scene, int i)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	vecBC;
	t_v3	vecBA;
	t_v3	vecCA;
	t_v3	vecCB;
	t_v3	normal;
	t_v3	camera_ray;

	face = *((*scene).projected_triangle + i);
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vecAC = vec3_subtract(&(face.c), &(face.a));
	normal = vec3_cross(&vecAB, &vecAC);
	(*((*scene).projected_triangle + i)).p0.normal = normal;//****
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*scene).origin), &(face).a);
	vec3_normalize(&camera_ray);
	(*scene).dot = vec3_dot(&camera_ray, &normal);
	vec3_normalize(&normal);

	vecBC = vec3_subtract(&(face.c), &(face.b));
	vecBA = vec3_subtract(&(face.a), &(face.b));
	normal = vec3_cross(&vecBC, &vecBA);
	//vec3_normalize(&normal);
	(*((*scene).projected_triangle + i)).p1.normal = normal;//**

	vecCA = vec3_subtract(&(face.a), &(face.c));
	vecCB = vec3_subtract(&(face.b), &(face.c));
	normal = vec3_cross(&vecCA, &vecCB);
	//vec3_normalize(&normal);
	(*((*scene).projected_triangle + i)).p2.normal = normal;//**
	return ((*scene).dot);
}
