#include "header.h"

/*	pthread_mutex_t	*mutex_buffer;
	pthread_mutex_t code_mutex[THREAD_NUM];
	pthread_t		thread[THREAD_NUM];
*/

void	unlock_code_mutex(pthread_mutex_t *code_mutex, int thread_num)
{
	int i;

	i = -1;
	while (++i < thread_num)
		pthread_mutex_unlock(code_mutex + i);
}

void	lock_code_mutex(pthread_mutex_t *code_mutex, int thread_num)
{
	int i;

	i = -1;
	while (++i < thread_num)
		pthread_mutex_lock(code_mutex + i);
}


void	launch_threads(pthread_t *thread, void *arg)
{
	int	i;

	i = -1;
	
	while (++i < THREAD_NUM)
		pthread_create(thread + i, NULL, &start, arg);
}

pthread_mutex_t	*init_threads(t_scene *scene)
{
	static pthread_barrier_t		wait_triangle;
	static pthread_barrier_t		wait_main_lock;
	static pthread_barrier_t		first_wall;
	int								i;
	static t_arg					arg;
	static pthread_mutex_t			mutex_buffer[BUFF_SIZE];

	(*scene).arg = (void*)(&arg);
	pthread_barrier_init(&first_wall, NULL, THREAD_NUM + 1);	
	pthread_barrier_init(&wait_triangle, NULL, THREAD_NUM + 1);	
	pthread_barrier_init(&wait_main_lock, NULL, THREAD_NUM + 1);
	(*scene).wait_triangle = &wait_triangle;
	(*scene).wait_main_lock = &wait_main_lock;
	(*scene).first_wall = &first_wall;
	arg.pixel_info.wait_triangle = &wait_triangle;
	arg.pixel_info.wait_main_lock = &wait_main_lock;
	arg.pixel_info.first_wall = &first_wall;
	arg.pixel_info.scene = scene;
	(*scene).mutex_buffer = mutex_buffer;
	if ((*scene).mutex_buffer == NULL)
		return (NULL);
	i = -1;
	while (++i < BUFF_SIZE)
		pthread_mutex_init((*scene).mutex_buffer + i, NULL);
	i = -1;
	while (++i < MUTEX_NUM)
		pthread_mutex_init((*scene).code_mutex + i, NULL);
	launch_threads((*scene).thread, (*scene).arg);
	return ((*scene).mutex_buffer);
}
