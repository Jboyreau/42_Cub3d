#include "header.h"

static void	launch_threads(pthread_t *thread, void *arg)
{
	int	i;

	i = -1;	
	while (++i < THREAD_NUM)
		pthread_create(thread + i, NULL, &start, arg);
}

static void	init_barrier(t_scene *scene, t_arg *arg)
{
	static pthread_barrier_t		first_wall;
	static pthread_barrier_t		wait_triangle;

	pthread_barrier_init(&first_wall, NULL, THREAD_NUM + 1);	
	pthread_barrier_init(&wait_triangle, NULL, THREAD_NUM + 1);	
	(*scene).first_wall = &first_wall;
	(*scene).wait_triangle = &wait_triangle;
	(*arg).pixel_info.first_wall = &first_wall;
	(*arg).pixel_info.wait_triangle = &wait_triangle;
}

void	init_threads(t_scene *scene)
{
	static t_arg	arg;

	(*scene).arg = (void*)(&arg);
	arg.pixel_info.scene = scene;
	arg.pixel_info.screen_space_origin.x =  MIDLE_X;
	arg.pixel_info.screen_space_origin.y =  MIDLE_Y;	
	arg.pixel_info.screen_space_origin.z = -80;
	init_barrier(scene, &arg);
	launch_threads((*scene).thread, (*scene).arg);
}
