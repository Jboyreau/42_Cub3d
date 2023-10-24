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

	new.x = (*v0).x / factor;
	new.y = (*v0).y / factor;
	new.z = (*v0).z / factor;
	return (new);
}
