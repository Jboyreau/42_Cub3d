#ifndef HEADER_H
#define HEADER_H
#define ZOOM 10
# define HEIGHT 720
# define WIDTH 1280
# define BUFF_SIZE 921600 //HEIGHT * WIDTH
# define CLEAR_SIZE 460800 //(HEIGHT * WIDTH) / 2

typedef struct s_canvas
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				*color_buffer;
	SDL_Texture		*color_buffer_texture;
} t_w;

typedef struct s_2dvector
{
	float		x;
	float		y;
} t_v2;

typedef struct s_3dvector
{
	float		x;
	float		y;
	float		z;
} t_v3;

typedef struct s_camera
{
	t_v3	position;
	t_v3	rotation;
	float	fov;
} t_cam;

typedef struct s_scene //what I project
{
	float	zoom;
	t_v3	*cloud;
	int		*color_buffer;
} t_scene;

typedef struct t_keys
{
	int		key;
	int		wheel;
	int		mouse_wheel_event;
} t_keys;

typedef struct s_funarrays
{
	char		(*fun_update[65537])(t_scene *);
	int			(*fun_event[128])(t_keys *);
} t_f;

//point cloud
void	make_cube(t_v3 *cube);

//init
void 	initialize_fun(t_f *fun);
void	initialize_scene(t_scene *scene, t_v3 *cloud, int *color_buffer, int zoom);

//process input
int		process_input(int (*fun_event[])(t_keys *));
int		set_nothing(t_keys *);
int		set_quit(t_keys *);
int		set_index(t_keys *);

//update / projection
void	clear_color_buffer(int *color_buffer);
char	nothing(t_scene *scene);
char	quit(t_scene *scene);
char 	ortho_project(t_scene *scene);
char 	ortho_project_zoom_plus(t_scene *scene);
char 	ortho_project_zoom_minus(t_scene *scene);

//renderer
char	display(t_w *canvas, char status);

#endif
