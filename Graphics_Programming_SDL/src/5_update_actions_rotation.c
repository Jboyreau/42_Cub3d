#include "header.h"

char	camera_rotation_x_minus(t_scene *scene)
{
	float	y, z;
	int		i = 0;

	(*scene).camera.rotation.x += ROTATION_INC_MINUS;
	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) - y * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_MINUS) + z * sin(ROTATION_INC_MINUS);
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	camera_rotation_x_plus(t_scene *scene)
{
	float	y, z;
	int		i = 0;

	(*scene).camera.rotation.x += ROTATION_INC_PLUS;
	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) - y * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_PLUS) + z * sin(ROTATION_INC_PLUS);
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	camera_rotation_y_minus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	(*scene).camera.rotation.y += ROTATION_INC_MINUS;
	while (i < (*scene).cloud_size)
	{
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) + x * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_MINUS) - z * sin(ROTATION_INC_MINUS);
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	camera_rotation_y_plus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	(*scene).camera.rotation.y += ROTATION_INC_PLUS;
	while (i < (*scene).cloud_size)
	{
		x = (*((*scene).cloud + i)).x;
		z = (*((*scene).cloud + i)).z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) + x * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_PLUS) - z * sin(ROTATION_INC_PLUS);
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

void	rotation_x(t_scene *scene, int i, float angle)
{
	float	y, z;

	y = (*((*scene).cloud + i)).y;
	z = (*((*scene).cloud + i)).z;
	(*((*scene).cloud + i)).z = z * cos(angle) - y * sin(angle);
	(*((*scene).cloud + i)).y = y * cos(angle) + z * sin(angle);
}

void	rotation_y(t_scene *scene, int i, float angle)
{
	float	x, z;

	x = (*((*scene).cloud + i)).x;
	z = (*((*scene).cloud + i)).z;
	(*((*scene).cloud + i)).z = z * cos(angle) + x * sin(angle);
	(*((*scene).cloud + i)).x = x * cos(angle) - z * sin(angle);
}

char	rotation_x_minus(t_scene *scene)
{
	float	y, z;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{
		//rev_rot
		rotation_x(scene, i, -((*scene).camera.rotation.x));
		rotation_y(scene, i, -((*scene).camera.rotation.y));
		y = (*((*scene).cloud + i)).y - (*scene).camera.position.y;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) - y * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_MINUS) + z * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		//aply_rot
		rotation_x(scene, i, ((*scene).camera.rotation.x));
		rotation_y(scene, i, ((*scene).camera.rotation.y));
		++i;
	}
	perspective_project(scene);
	return (1);
}

char	rotation_x_plus(t_scene *scene)
{
	float	y, z;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{
		//rev_rot
		rotation_x(scene, i, -((*scene).camera.rotation.x));
		rotation_y(scene, i, -((*scene).camera.rotation.y));
		y = (*((*scene).cloud + i)).y - (*scene).camera.position.y;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) - y * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_PLUS) + z * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		//aply_rot
		rotation_x(scene, i, ((*scene).camera.rotation.x));
		rotation_y(scene, i, ((*scene).camera.rotation.y));
		++i;
	}	
	perspective_project(scene);
	return (1);
}

char	rotation_y_minus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{
		//rev_rot
		rotation_x(scene, i, -((*scene).camera.rotation.x));
		rotation_y(scene, i, -((*scene).camera.rotation.y));
		x = (*((*scene).cloud + i)).x - (*scene).camera.position.x;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) + x * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_MINUS) - z * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		//aply_rot
		rotation_x(scene, i, ((*scene).camera.rotation.x));
		rotation_y(scene, i, ((*scene).camera.rotation.y));
		++i;
	}
	perspective_project(scene);
	return (1);
}

char	rotation_y_plus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{
		//rev_rot
		rotation_x(scene, i, -((*scene).camera.rotation.x));
		rotation_y(scene, i, -((*scene).camera.rotation.y));
		x = (*((*scene).cloud + i)).x - (*scene).camera.position.x;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) + x * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_PLUS) - z * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		//aply_rot
		rotation_x(scene, i, ((*scene).camera.rotation.x));
		rotation_y(scene, i, ((*scene).camera.rotation.y));
		++i;
	}
	perspective_project(scene);
	return (1);
}

char	rotation_z_minus(t_scene *scene)
{
	float	x, y;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{
		//rev_rot
		rotation_x(scene, i, -((*scene).camera.rotation.x));
		rotation_y(scene, i, -((*scene).camera.rotation.y));
		x = (*((*scene).cloud + i)).x - (*scene).camera.position.x;
		y = (*((*scene).cloud + i)).y - (*scene).camera.position.y;
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_MINUS) + y * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_MINUS) - x * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		//aply_rot
		rotation_x(scene, i, ((*scene).camera.rotation.x));
		rotation_y(scene, i, ((*scene).camera.rotation.y));
		++i;
	}
	perspective_project(scene);	
	return (1);
}

char	rotation_z_plus(t_scene *scene)
{
	float	x, y;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{
		//rev_rot
		rotation_x(scene, i, -((*scene).camera.rotation.x));
		rotation_y(scene, i, -((*scene).camera.rotation.y));
		x = (*((*scene).cloud + i)).x - (*scene).camera.position.x;
		y = (*((*scene).cloud + i)).y - (*scene).camera.position.y;
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_PLUS) + y * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_PLUS) - x * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		//aply_rot
		rotation_x(scene, i, ((*scene).camera.rotation.x));
		rotation_y(scene, i, ((*scene).camera.rotation.y));
		++i;
	}
	perspective_project(scene);
	return (1);
}
