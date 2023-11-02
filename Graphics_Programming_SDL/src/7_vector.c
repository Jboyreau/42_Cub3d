#include "header.h"

float	vec2_length(t_v2 *vector)
{
	return (sqrt((*vector).x * (*vector).x + (*vector).y * (*vector).y));
}

float	vec3_length(t_v3 *vector)
{
	return (sqrt((*vector).x * (*vector).x + (*vector).y * (*vector).y + (*vector).z * (*vector).z));
}

t_v2	vec2_subtract(t_v2 *v0, t_v2 *v1)
{
	t_v2 sum;

	sum.x = (*v0).x - (*v1).x;
	sum.y = (*v0).y - (*v1).y;
	return (sum);
}

t_v3	vec3_subtract(t_v3 *v0, t_v3 *v1)
{
	t_v3 sum;

	sum.x = (*v0).x - (*v1).x;
	sum.y = (*v0).y - (*v1).y;
	sum.z = (*v0).z - (*v1).z;
	return (sum);
}

t_v2	vec2_addition(t_v2 *v0, t_v2 *v1)
{
	t_v2 sum;

	sum.x = (*v0).x + (*v1).x;
	sum.y = (*v0).y + (*v1).y;
	return (sum);
}

t_v3	vec3_addition(t_v3 *v0, t_v3 *v1)
{
	t_v3 sum;

	sum.x = (*v0).x + (*v1).x;
	sum.y = (*v0).y + (*v1).y;
	sum.z = (*v0).z + (*v1).z;
	return (sum);
}

t_v2	vec2_multiplication(t_v2 *v0, float factor)
{
	t_v2 new;

	new.x = (*v0).x * factor;
	new.y = (*v0).y * factor;
	return (new);
}

t_v3	vec3_multiplication(t_v3 *v0, float factor)
{
	t_v3 new;

	new.x = (*v0).x * factor;
	new.y = (*v0).y * factor;
	new.z = (*v0).z * factor;
	return (new);
}

t_v2	vec2_divizion(t_v2 *v0, float factor)
{
	t_v2 new;

	new.x = (*v0).x / factor;
	new.y = (*v0).y / factor;
	return (new);
}

t_v3	vec3_divizion(t_v3 *v0, float factor)
{
	t_v3 new;

	factor = 1 / factor;
	new.x = (*v0).x * factor;
	new.y = (*v0).y * factor;
	new.z = (*v0).z * factor;
	return (new);
}

t_v3	vec3_cross(t_v3 *a, t_v3 *b)
{
	t_v3 normal;

	normal.x = ((*a).y * (*b).z) - ((*a).z * (*b).y);
	normal.y = ((*a).z * (*b).x) - ((*a).x * (*b).z);
	normal.z = ((*a).x * (*b).y) - ((*a).y * (*b).x);
	return (normal);
}

float	vec2_dot(t_v2 *a, t_v2 *b)
{
	return (((*a).x * (*b).x) + ((*a).y * (*b).y));
}

float	vec3_dot(t_v3 *a, t_v3 *b)
{
	return (((*a).x * (*b).x) + ((*a).y * (*b).y) + ((*a).z * (*b).z));
}

float	vec3_normalize_r(t_v3 *vec)
{
	float len = vec3_length(vec);
	(*vec) = vec3_divizion(vec, len);
	return (len);
}

void	vec3_denormalize(t_v3 *vec, float len)
{
	(*vec) = vec3_multiplication(vec, len);
}

void	vec3_normalize(t_v3 *vec)
{
	(*vec) = vec3_divizion(vec, vec3_length(vec));
}

void	vec2_normalize(t_v2 *vec)
{
	(*vec) = vec2_divizion(vec, vec2_length(vec));
}
