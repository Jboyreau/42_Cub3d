#include "header.h"

float is_visible(t_scene *scene, int i)
{
	t_ptri	face;
	t_v3	vecAB;
	t_v3	vecAC;
	t_v3	normal;
	t_v3	camera_ray;

	face.a = *((*scene).cloud + (*((*scene).triangle_index + i)).a);
	face.b = *((*scene).cloud + (*((*scene).triangle_index + i)).b);
	face.c = *((*scene).cloud + (*((*scene).triangle_index + i)).c);
	face.a.z += (*scene).dist;
	face.b.z += (*scene).dist;
	face.c.z += (*scene).dist;
	vecAB = vec3_subtract(&(face.b), &(face.a));
	vec3_normalize(&vecAB);
	vecAC = vec3_subtract(&(face.c), &(face.a));
	vec3_normalize(&vecAC);
	normal = vec3_cross(&vecAB, &vecAC);
	vec3_normalize(&normal);
	camera_ray = vec3_subtract(&((*scene).camera.position), &(face).a);
	vec3_normalize(&camera_ray);
	return (vec3_dot(&camera_ray, &normal));
}
