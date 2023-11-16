#include "header.h" 

static void	vertex_to_color_buffer(t_scene *scene, t_v3 *vertex)
{
	(*vertex).inv_z = 1 / (*vertex).z;
	(*vertex).x = ((*vertex).x * (*scene).scale) * (*vertex).inv_z + MIDLE_X;
	(*vertex).y = ((*vertex).y * (*scene).scale) * (*vertex).inv_z + MIDLE_Y;
}

void	triangle_to_color_buffer(t_scene *scene, int i, t_pixel_info *pixel_info)
{
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).a);
	(*((*scene).projected_triangle + i)).p0.x = (*((*scene).projected_triangle + i)).a.x;
	(*((*scene).projected_triangle + i)).p0.y = (*((*scene).projected_triangle + i)).a.y;
	(*((*scene).projected_triangle + i)).p0.z = (*((*scene).projected_triangle + i)).a.z;
	(*((*scene).projected_triangle + i)).p0.inv_z = (*((*scene).projected_triangle + i)).a.inv_z;
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).b);
	(*((*scene).projected_triangle + i)).p1.x = (*((*scene).projected_triangle + i)).b.x;
	(*((*scene).projected_triangle + i)).p1.y = (*((*scene).projected_triangle + i)).b.y;
	(*((*scene).projected_triangle + i)).p1.z = (*((*scene).projected_triangle + i)).b.z;
	(*((*scene).projected_triangle + i)).p1.inv_z = (*((*scene).projected_triangle + i)).b.inv_z;
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).c);
	(*((*scene).projected_triangle + i)).p2.x = (*((*scene).projected_triangle + i)).c.x;
	(*((*scene).projected_triangle + i)).p2.y = (*((*scene).projected_triangle + i)).c.y;
	(*((*scene).projected_triangle + i)).p2.z = (*((*scene).projected_triangle + i)).c.z;
	(*((*scene).projected_triangle + i)).p2.inv_z = (*((*scene).projected_triangle + i)).c.inv_z;
	
	launch(scene, pixel_info, i);
}

void	triangle_to_nowhere(t_scene *scene, int i, t_pixel_info *pixel_info)
{
	(void)scene;
	(void)i;
	(void)pixel_info;
}

void	launch(t_scene *scene, t_pixel_info *pixel_info, int i)
{
		(*(*scene).fun).draw_ft[
		(((*((*scene).projected_triangle + i)).p0.y < (*((*scene).projected_triangle + i)).p2.y) && ((*((*scene).projected_triangle + i)).p2.y < (*((*scene).projected_triangle + i)).p1.y))
		+ ((((*((*scene).projected_triangle + i)).p1.y < (*((*scene).projected_triangle + i)).p0.y) && ((*((*scene).projected_triangle + i)).p0.y <= (*((*scene).projected_triangle + i)).p2.y)) << 1)
		+ ((((*((*scene).projected_triangle + i)).p1.y < (*((*scene).projected_triangle + i)).p2.y) && ((*((*scene).projected_triangle + i)).p2.y < (*((*scene).projected_triangle + i)).p0.y)) << 2)
		+ ((((*((*scene).projected_triangle + i)).p2.y < (*((*scene).projected_triangle + i)).p0.y) && ((*((*scene).projected_triangle + i)).p0.y < (*((*scene).projected_triangle + i)).p1.y)) << 3)
		+ ((((*((*scene).projected_triangle + i)).p2.y < (*((*scene).projected_triangle + i)).p1.y) && ((*((*scene).projected_triangle + i)).p1.y < (*((*scene).projected_triangle + i)).p0.y)) << 4)

		+ ((((*((*scene).projected_triangle + i)).p0.y < (*((*scene).projected_triangle + i)).p1.y) && ((*((*scene).projected_triangle + i)).p1.y == (*((*scene).projected_triangle + i)).p2.y)))
		+ ((((*((*scene).projected_triangle + i)).p0.y > (*((*scene).projected_triangle + i)).p1.y) && ((*((*scene).projected_triangle + i)).p1.y == (*((*scene).projected_triangle + i)).p2.y)) << 2)
		+ ((((*((*scene).projected_triangle + i)).p1.y < (*((*scene).projected_triangle + i)).p0.y) && ((*((*scene).projected_triangle + i)).p0.y == (*((*scene).projected_triangle + i)).p2.y)) << 1)
		+ ((((*((*scene).projected_triangle + i)).p1.y > (*((*scene).projected_triangle + i)).p0.y) && ((*((*scene).projected_triangle + i)).p0.y == (*((*scene).projected_triangle + i)).p2.y)))
		+ ((((*((*scene).projected_triangle + i)).p2.y < (*((*scene).projected_triangle + i)).p1.y) && ((*((*scene).projected_triangle + i)).p1.y == (*((*scene).projected_triangle + i)).p0.y)) << 3)
		+ ((((*((*scene).projected_triangle + i)).p2.y > (*((*scene).projected_triangle + i)).p1.y) && ((*((*scene).projected_triangle + i)).p1.y == (*((*scene).projected_triangle + i)).p0.y)) << 1)
	](pixel_info, i);
}


void	dont_launch(t_scene *scene, t_pixel_info *pixel_info, int i)
{
	(void)scene;
	(void)pixel_info;
	(void)i;
}

char	camera_perspective_project(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int				j;
	int				i;

	clear_color_buffer(((long long int *)((*scene).color_buffer)), (*scene).z_buffer);
	pixel_info.scene = scene;
	i = -1;
	while (++i < (*scene).triangle_index_size)
	{
		pixel_info.depth =
			(*((*scene).cloud + (*((*scene).triangle_index + i)).a)).z
			+ (*((*scene).cloud + (*((*scene).triangle_index + i)).b)).z
			+ (*((*scene).cloud + (*((*scene).triangle_index + i)).c)).z;
		poly_to_tri(scene, tri_to_poly(scene, (*scene).triangle_index + i));
		j = -1;
		while (++j < (*scene).nb_tri)
			(*(*scene).fun).culling[(is_visible(scene, j) >= 0)](scene, j, &pixel_info);
	}
	return (1);
}

char	perspective_project(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int				i;
	int				j;

	clear_color_buffer(((long long int *)((*scene).color_buffer)), (*scene).z_buffer);
	pixel_info.scene = scene;
	i = -1;
	while(++i < (*scene).cloud_size)
	{
		rev_camera_rotation_x(scene, i, -(*scene).camera.rotation.x);
		(*((*scene).cloud + i)).x += (*scene).pos_incx;
		(*((*scene).cloud + i)).y += (*scene).pos_incy;
		(*((*scene).cloud + i)).z += (*scene).pos_incz;
		rev_camera_rotation_x(scene, i, (*scene).camera.rotation.x);
	}
	i = -1;
	while (++i < (*scene).triangle_index_size)
	{
		pixel_info.depth =
			(*((*scene).cloud + (*((*scene).triangle_index + i)).a)).z
			+ (*((*scene).cloud + (*((*scene).triangle_index + i)).b)).z
			+ (*((*scene).cloud + (*((*scene).triangle_index + i)).c)).z;
		poly_to_tri(scene, tri_to_poly(scene, (*scene).triangle_index + i));
		j = -1;
		while (++j < (*scene).nb_tri)
			(*(*scene).fun).culling[(is_visible(scene, j) >= 0)](scene, j, &pixel_info);
	}
	(*scene).pos_incx = 0;
	(*scene).pos_incy = 0;
	(*scene).pos_incz = 0;
	return (1);
}

char	perspective_project_far(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position), -(*scene).camera.rotation.x);
	(*scene).camera.position.z += DIST_INC;
	(*scene).pos_incz = DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position), (*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_close(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position), -(*scene).camera.rotation.x);
	(*scene).camera.position.z -= DIST_INC;
	(*scene).pos_incz = -DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position), (*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_down(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position), -(*scene).camera.rotation.x);
	(*scene).camera.position.y += DIST_INC;
	(*scene).pos_incy = DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position), (*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_up(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position), -(*scene).camera.rotation.x);
	(*scene).camera.position.y -= DIST_INC;
	(*scene).pos_incy = -DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position), (*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_right(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position), -(*scene).camera.rotation.x);
	(*scene).camera.position.x += DIST_INC;
	(*scene).pos_incx = DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position), (*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_left(t_scene *scene)
{
	rev_camera_rotation_origin_x(&((*scene).camera.position), -(*scene).camera.rotation.x);
	(*scene).camera.position.x -= DIST_INC;
	(*scene).pos_incx = -DIST_INC;
	rev_camera_rotation_origin_x(&((*scene).camera.position), (*scene).camera.rotation.x);
	return (perspective_project(scene));
}

char	perspective_project_zoom_plus(t_scene *scene)
{
	(*scene).scale += SCALE_INC * ((*scene).scale + SCALE_INC < 1000);
	return (perspective_project(scene));
}

char	perspective_project_zoom_minus(t_scene *scene)
{
	(*scene).scale -= SCALE_INC;
	return (perspective_project(scene));
}
