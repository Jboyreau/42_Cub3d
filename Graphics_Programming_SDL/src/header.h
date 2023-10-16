#ifndef HEADER_H
#define HEADER_H
#define SCALE 50
#define SCALE_INC 10
# define HEIGHT 720
# define WIDTH 1280
# define BUFF_SIZE 921600 //HEIGHT * WIDTH
# define CLEAR_SIZE 460800 //(HEIGHT * WIDTH) / 2
#define MODEL_SIZE 729
#define MIDLE_X 640
#define MIDLE_Y 360
#define Z_VALUE 5
#define DIST_INC 0.25
#define ROTATION_INC_PLUS 0.1
#define ROTATION_INC_MINUS -0.1

typedef struct s_canvas
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				*color_buffer;
	SDL_Texture		*color_buffer_texture;
} t_w;

typedef struct s_2dvector
{
	float		op;
	float		adj;
} t_v2;

typedef struct s_3dvector
{
	float		x;
	float		y;
	float		z;
	float		inv_z;
} t_v3;

typedef struct s_camera
{
	t_v3	position;
	t_v3	rotation;
	float	fov;
} t_cam;

typedef struct s_funarrays t_f;

typedef struct s_scene //what I project
{
	int		scale;
	float	dist;
	//t_v3	rotation;
	t_v3	*cloud;
	int		*color_buffer;
	t_f		*fun;
	
} t_scene;

typedef struct t_keys
{
	int		key;
	int		wheel;
	int		mouse_wheel_event;
} t_keys;

typedef struct s_pixel_info
{
	t_scene	*scene;
	int 	cell;
} t_pixel_info;

struct s_funarrays
{
	char	(*fun_update[65537])(t_scene *);
	int		(*fun_event[128])(t_keys *);
	void	(*fun_draw_pixel[128])(t_pixel_info *);
};

//point cloud
void	make_cube(t_v3 *cube);

//init
void 	initialize_fun(t_f *fun);
t_scene	*initialize_scene(t_v3 *cloud, int *color_buffer, int zoom, t_f *fun);

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
char	perspective_project_zoom_plus(t_scene *scene);
char	perspective_project_zoom_minus(t_scene *scene);
char	perspective_project(t_scene *scene);
char	perspective_project_close(t_scene *scene);
char	perspective_project_far(t_scene *scene);
char	rotation_x_minus(t_scene *scene);
char	rotation_x_plus(t_scene *scene);
char	rotation_y_minus(t_scene *scene);
char	rotation_y_plus(t_scene *scene);
void	draw_pixel(t_pixel_info *pixel_info);
void	do_not_draw_pixel(t_pixel_info *pixel_info);

//renderer
char	display(t_w *canvas, char status);

#endif
