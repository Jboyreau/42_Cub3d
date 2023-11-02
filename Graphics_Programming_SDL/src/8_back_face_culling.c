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
	
	/*face.a.z += (*scene).camera.position.z;
	face.b.z += (*scene).camera.position.z;
	face.c.z += (*scene).camera.position.z;
	
	face.a.x += (*scene).camera.position.x;
	face.b.x += (*scene).camera.position.x;
	face.c.x += (*scene).camera.position.x;
	
	face.a.y += (*scene).camera.position.y;
	face.b.y += (*scene).camera.position.y;
	face.c.y += (*scene).camera.position.y;*/

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
