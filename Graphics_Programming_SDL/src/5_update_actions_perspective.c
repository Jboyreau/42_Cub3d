#include "header.h" 

static void	vertex_to_color_buffer(t_scene *scene, t_v3 *vertex, int i_cloud)
{
	(*vertex).inv_z = 1 / ((*((*scene).cloud + i_cloud)).z);
	(*vertex).x = ((*((*scene).cloud + i_cloud)).x * (*scene).scale) * (*vertex).inv_z + MIDLE_X;
	(*vertex).y = ((*((*scene).cloud + i_cloud)).y * (*scene).scale) * (*vertex).inv_z + MIDLE_Y;
	(*vertex).z = (*((*scene).cloud + i_cloud)).z;
}

void	triangle_to_color_buffer(t_scene *scene, int i, t_pixel_info *pixel_info)
{
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).a, (*((*scene).triangle_index + i)).a);
	(*((*scene).projected_triangle + i)).p0.x = (*((*scene).projected_triangle + i)).a.x;
	(*((*scene).projected_triangle + i)).p0.y = (*((*scene).projected_triangle + i)).a.y;
	(*((*scene).projected_triangle + i)).p0.z = (*((*scene).projected_triangle + i)).a.z;
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).b, (*((*scene).triangle_index + i)).b);
	(*((*scene).projected_triangle + i)).p1.x = (*((*scene).projected_triangle + i)).b.x;
	(*((*scene).projected_triangle + i)).p1.y = (*((*scene).projected_triangle + i)).b.y;
	(*((*scene).projected_triangle + i)).p1.z = (*((*scene).projected_triangle + i)).b.z;
	vertex_to_color_buffer(scene, &(*((*scene).projected_triangle + i)).c, (*((*scene).triangle_index + i)).c);
	(*((*scene).projected_triangle + i)).p2.x = (*((*scene).projected_triangle + i)).c.x;
	(*((*scene).projected_triangle + i)).p2.y = (*((*scene).projected_triangle + i)).c.y;
	(*((*scene).projected_triangle + i)).p2.z = (*((*scene).projected_triangle + i)).c.z;
	
	(*(*scene).fun).start_draw_ft[(
		(*((*scene).projected_triangle + i)).p0.x > WIDTH
		|| (*((*scene).projected_triangle + i)).p0.y > HEIGHT
		|| (*((*scene).projected_triangle + i)).p1.x > WIDTH
		|| (*((*scene).projected_triangle + i)).p1.y > HEIGHT
		|| (*((*scene).projected_triangle + i)).p2.x > WIDTH
		|| (*((*scene).projected_triangle + i)).p2.y > HEIGHT
		|| (*((*scene).projected_triangle + i)).p0.x < 0
		|| (*((*scene).projected_triangle + i)).p0.y < 0
		|| (*((*scene).projected_triangle + i)).p1.x < 0
		|| (*((*scene).projected_triangle + i)).p1.y < 0
		|| (*((*scene).projected_triangle + i)).p2.x < 0
		|| (*((*scene).projected_triangle + i)).p2.y < 0)
	](scene, pixel_info, i);
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
	int				i = -1;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)), (*scene).z_buffer);
	pixel_info.scene = scene;
	while (++i < (*scene).triangle_index_size)
		(*(*scene).fun).culling[(
			(*((*scene).cloud + (*((*scene).triangle_index + i)).a)).z > 0
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).b)).z > 0
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).c)).z > 0
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).a)).z < 10
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).b)).z < 10
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).c)).z < 10
			&& is_visible(scene, i) >= 0)
		](scene, i, &pixel_info);
	return (1);
}

char	perspective_project(t_scene *scene)
{
	t_pixel_info	pixel_info;
	int				i = -1;

	//clear_color_buffer((*scene).color_buffer);
	clear_color_buffer(((long long int *)((*scene).color_buffer)), (*scene).z_buffer);
	pixel_info.scene = scene;
	while(++i < (*scene).cloud_size)
	{
		(*((*scene).cloud + i)).x += (*scene).pos_incx;
		(*((*scene).cloud + i)).y += (*scene).pos_incy;
		(*((*scene).cloud + i)).z += (*scene).pos_incz;
	}
	i = -1;
	while (++i < (*scene).triangle_index_size)
		(*(*scene).fun).culling[(
			(*((*scene).cloud + (*((*scene).triangle_index + i)).a)).z > 0
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).b)).z > 0
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).c)).z > 0
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).a)).z < 10
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).b)).z < 10
			&& (*((*scene).cloud + (*((*scene).triangle_index + i)).c)).z < 10
			&& is_visible(scene, i) >= 0)
		](scene, i, &pixel_info);	
	(*scene).pos_incx = 0;
	(*scene).pos_incy = 0;
	(*scene).pos_incz = 0;
	return (1);
}

char	perspective_project_far(t_scene *scene)
{
	(*scene).camera.position.z += DIST_INC;
	//(*scene).radius = vec3_length(&((*scene).camera.position));
	(*scene).pos_incz = DIST_INC;
	return (perspective_project(scene));
}

char	perspective_project_close(t_scene *scene)
{
	(*scene).camera.position.z -= DIST_INC;
	//(*scene).radius = vec3_length(&((*scene).camera.position));
	(*scene).pos_incz = -DIST_INC;
	return (perspective_project(scene));
}

char	perspective_project_down(t_scene *scene)
{
	(*scene).camera.position.y += DIST_INC;
	//(*scene).radius = vec3_length(&((*scene).camera.position));
	(*scene).pos_incy = DIST_INC;
	return (perspective_project(scene));
}

char	perspective_project_up(t_scene *scene)
{
	(*scene).camera.position.y -= DIST_INC;
	//(*scene).radius = vec3_length(&((*scene).camera.position));
	(*scene).pos_incy = -DIST_INC;
	return (perspective_project(scene));
}

char	perspective_project_right(t_scene *scene)
{
	(*scene).camera.position.x += DIST_INC;
	//(*scene).radius = vec3_length(&((*scene).camera.position));
	(*scene).pos_incx = DIST_INC;
	return (perspective_project(scene));
}

char	perspective_project_left(t_scene *scene)
{
	(*scene).camera.position.x -= DIST_INC;
	//(*scene).radius = vec3_length(&((*scene).camera.position));
	(*scene).pos_incx = -DIST_INC;
	return (perspective_project(scene));
}

char	perspective_project_zoom_plus(t_scene *scene)
{
	(*scene).scale += SCALE_INC;
	return (perspective_project(scene));
}

char	perspective_project_zoom_minus(t_scene *scene)
{
	(*scene).scale -= SCALE_INC;
	return (perspective_project(scene));
}
