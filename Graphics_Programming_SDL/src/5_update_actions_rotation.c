#include "header.h"

char	camera_rotation_x_minus(t_scene *scene)
{
	float	y, z;
	int		i = 0;

	y = (*scene).camera.position.y;
	z = (*scene).camera.position.z;
	(*scene).camera.position.z = (z * cos(ROTATION_INC_MINUS) - y * sin(ROTATION_INC_MINUS));
	(*scene).camera.position.y = (y * cos(ROTATION_INC_MINUS) + z * sin(ROTATION_INC_MINUS));
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

	y = (*scene).camera.position.y;
	z = (*scene).camera.position.z;
	(*scene).camera.position.z = (z * cos(ROTATION_INC_PLUS) - y * sin(ROTATION_INC_PLUS));
	(*scene).camera.position.y = (y * cos(ROTATION_INC_PLUS) + z * sin(ROTATION_INC_PLUS));
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

	x = (*scene).camera.position.x;
	z = (*scene).camera.position.z;
	(*scene).camera.position.z = (z * cos(ROTATION_INC_MINUS) + x * sin(ROTATION_INC_MINUS));
	(*scene).camera.position.x = (x * cos(ROTATION_INC_MINUS) - z * sin(ROTATION_INC_MINUS));
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

	x = (*scene).camera.position.x;
	z = (*scene).camera.position.z;
	(*scene).camera.position.z = (z * cos(ROTATION_INC_PLUS) + x * sin(ROTATION_INC_PLUS));
	(*scene).camera.position.x = (x * cos(ROTATION_INC_PLUS) - z * sin(ROTATION_INC_PLUS));
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

/***************************************************************************************/

char	rotation_x_minus(t_scene *scene)
{
	float	y, z;
	int		i = 0;
 
	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y - (*scene).camera.position.y;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		
		//rotation
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) - y * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_MINUS) + z * sin(ROTATION_INC_MINUS);
		
		//apply_trans and rot
		//(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	rotation_x_plus(t_scene *scene)
{
	float	y, z;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{
		y = (*((*scene).cloud + i)).y - (*scene).camera.position.y;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		
		//rotation
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) - y * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).y = y * cos(ROTATION_INC_PLUS) + z * sin(ROTATION_INC_PLUS);
		
		//apply_trans and rot
		//(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	rotation_y_minus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{
		//rev_trans
		x = (*((*scene).cloud + i)).x - (*scene).camera.position.x;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		
		//rotation
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_MINUS) + x * sin(ROTATION_INC_MINUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_MINUS) - z * sin(ROTATION_INC_MINUS);
		
		//apply_tans
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	rotation_y_plus(t_scene *scene)
{
	float	x, z;
	int		i = 0;

	while (i < (*scene).cloud_size)
	{	
		//rev_trans
		x = (*((*scene).cloud + i)).x - (*scene).camera.position.x;
		z = (*((*scene).cloud + i)).z - (*scene).camera.position.z;
		
		//rotation
		(*((*scene).cloud + i)).z = z * cos(ROTATION_INC_PLUS) + x * sin(ROTATION_INC_PLUS);
		(*((*scene).cloud + i)).x = x * cos(ROTATION_INC_PLUS) - z * sin(ROTATION_INC_PLUS);
		
		//apply_tans
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		++i;
	}
	camera_perspective_project(scene);
	return (1);
}

char	rotation_z_minus(t_scene *scene)
{
	/*int	i = 0;
	(*scene).radius = 5;
	while (i < (*scene).cloud_size)
	{
		//rev_rot
		(*((*scene).cloud + i)).x -= (*((*scene).cloud + i)).rx;
		(*((*scene).cloud + i)).y -= (*((*scene).cloud + i)).ry;
		(*((*scene).cloud + i)).z -= (*((*scene).cloud + i)).rz;
		
		//rev_trans
		(*((*scene).cloud + i)).x -= (*scene).camera.position.x;
		(*((*scene).cloud + i)).y -= (*scene).camera.position.y;
		(*((*scene).cloud + i)).z -= (*scene).camera.position.z;
		++i;
	}
	camera_perspective_project(scene);
	(*scene).radius = 0;*/
	(void)scene;
	return (1);
}

char	rotation_z_plus(t_scene *scene)
{
	/*int	i = 0;
	(*scene).radius = 0;
	while (i < (*scene).cloud_size)
	{
		//apply_tans
		(*((*scene).cloud + i)).x += (*scene).camera.position.x;
		(*((*scene).cloud + i)).y += (*scene).camera.position.y;
		(*((*scene).cloud + i)).z += (*scene).camera.position.z;
		
		//apply_rot
		(*((*scene).cloud + i)).x += (*((*scene).cloud + i)).rx;
		(*((*scene).cloud + i)).y += (*((*scene).cloud + i)).ry;
		(*((*scene).cloud + i)).z += (*((*scene).cloud + i)).rz;
		++i;
	}
	camera_perspective_project(scene);
	(*scene).radius = 0;*/
	(void)scene;
	return (1);
}
