#include "header.h"

static void	launch_threads(pthread_t *thread, void *arg)
{
	int	i;

	i = -1;	
	while (++i < THREAD_NUM)
		pthread_create(thread + i, NULL, &start, arg);
}

static void	init_code_mutex(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < MUTEX_NUM)
		pthread_mutex_init((*scene).code_mutex + i, NULL);
}

static void	init_barrier(t_scene *scene, t_arg *arg)
{
	static pthread_barrier_t		first_wall;
	static pthread_barrier_t		wait_triangle;
	static pthread_barrier_t		start_transform;
	static pthread_barrier_t		wait_transform;

	pthread_barrier_init(&first_wall, NULL, THREAD_NUM + 1);	
	pthread_barrier_init(&wait_triangle, NULL, THREAD_NUM + 1);	
	pthread_barrier_init(&start_transform, NULL, THREAD_NUM + 1);
	pthread_barrier_init(&wait_transform, NULL, THREAD_NUM + 1);
	(*scene).first_wall = &first_wall;
	(*scene).wait_triangle = &wait_triangle;
	(*scene).start_transform = &start_transform;
	(*scene).wait_transform = &wait_transform;
	(*arg).pixel_info.first_wall = &first_wall;
	(*arg).pixel_info.wait_triangle = &wait_triangle;
	(*arg).pixel_info.wait_main_lock = &start_transform;
	(*arg).pixel_info.wait_main_lock = &wait_transform;
}

void	init_threads(t_scene *scene)
{
	static t_arg	arg;

	(*scene).arg = (void*)(&arg);
	arg.pixel_info.scene = scene;
	arg.pixel_info.screen_space_origin.x =  MIDLE_X;
	arg.pixel_info.screen_space_origin.y =  MIDLE_Y;	
	arg.pixel_info.screen_space_origin.z = -100;
	init_barrier(scene, &arg);
	init_code_mutex(scene);
	launch_threads((*scene).thread, (*scene).arg);
}
