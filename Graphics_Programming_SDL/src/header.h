#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <SDL2/SDL.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

//# define OBJ "./obj/cow/cow.obj"
//# define Z_VALUE 2000//cow

//# define OBJ "./obj/Skull/Skull_Low_Poly.obj"
//# define Z_VALUE 500//skull

//# define OBJ "./obj/f22/f22.obj"
//# define Z_VALUE 5//f22

//# define OBJ "./obj/book/book2.obj"
//# define Z_VALUE 5//book

//# define OBJ "./obj/floor/floor.obj"
//# define Z_VALUE 5//floor

# define OBJ "./obj/assault_rifle/AssaultRifle.obj"
# define Z_VALUE 5//AssaultRifle

//# define OBJ "./obj/famas/famas.obj"
//# define Z_VALUE 5//AssaultRifle

//# define OBJ "./obj/gundam/gundam.obj"
//# define Z_VALUE 5//AssaultRifle

//# define OBJ "./obj/sword/Short_Sword.obj"
//# define Z_VALUE 10//AssaultRifle

//# define OBJ "./obj/cube/cube.obj"
//# define Z_VALUE 5//AssaultRifle

//# define OBJ "./obj/bear/bear.obj"
//# define Z_VALUE 5//bear

# define FPS 80
# define FRAME_TARGET_TIME (1000 / FPS)
# define SCALE 500
# define SCALE_INC 10
# define HEIGHT 720
# define WIDTH 1280
# define BUFF_SIZE 921600 //HEIGHT * WIDTH
# define CLEAR_SIZE 460800 //(HEIGHT * WIDTH) / 2
//# define CUBE_SIZE 8
//# define CUBE_N_TRI 12
# define MIDLE_X 640
# define MIDLE_Y 360
# define DIST_INC 0.5
# define ROTATION_INC_PLUS 0.0872665
# define ROTATION_INC_MINUS -0.0872665

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
	float		inv_z;
} t_v3;

typedef struct s_camera
{
	t_v3	position;
	t_v3	rotation;
	float	fov;
} t_cam;

typedef struct s_funarrays t_f;

typedef struct s_tirangle
{
	int		a;
	int		b;
	int		c;
} t_tri;

typedef struct s_projected_tirangle
{
	t_v3	a;
	t_v3	b;
	t_v3	c;
} t_ptri;

typedef struct s_scene //what I project
{
	int		time_to_wait;
	int		previous_frame_time;
	int		scale;
	int		cloud_size;
	int		triangle_index_size;
	float	dist;
	//t_v3	rotation;
	t_v3	*cloud;
	t_tri	*triangle_index;
	t_ptri	*projected_triangle;
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

typedef struct s_dda
{
	int		delta_x;
	int		delta_y;
	int		abs_delta_x;
	int		abs_delta_y;
	t_v3	p1;
	t_v3	p2;	
} t_dda;

struct s_funarrays
{
	char	(*fun_update[65537])(t_scene *);
	int		(*fun_event[128])(t_keys *);
	void	(*fun_draw_pixel[128])(t_pixel_info *);
	void	(*fun_delay[128])(int);
	void	(*dda[128])(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
};

//point cloud generation
char	populate_3d_space(t_scene *scene);

//init
void 	initialize_fun(t_f *fun);
t_scene	*initialize_scene(int *color_buffer, t_f *fun);

//process input
int		process_input(int (*fun_event[])(t_keys *));
int		set_nothing(t_keys *);
int		set_quit(t_keys *);
int		set_index(t_keys *);

//update / projection
//void	clear_color_buffer(int *color_buffer);
void	clear_color_buffer(long long int *color_buffer);
char	nothing(t_scene *scene);
char	quit(t_scene *scene);
//char 	ortho_project(t_scene *scene);
//char 	ortho_project_zoom_plus(t_scene *scene);
//char 	ortho_project_zoom_minus(t_scene *scene);
void	triangle_to_color_buffer(t_scene *scene, int i, t_pixel_info *pixel_info);
char	perspective_project_zoom_plus(t_scene *scene);
char	perspective_project_zoom_minus(t_scene *scene);
char	perspective_project(t_scene *scene);
char	perspective_project_close(t_scene *scene);
char	perspective_project_far(t_scene *scene);

//linear transform
char	rotation_x_minus(t_scene *scene);
char	rotation_x_plus(t_scene *scene);
char	rotation_y_minus(t_scene *scene);
char	rotation_y_plus(t_scene *scene);
char	rotation_z_plus(t_scene *scene);
char	rotation_z_minus(t_scene *scene);

//triangle drawing
void	draw_triangle(t_scene *scene, t_pixel_info *pixel_info, int i);
void	dda_x_minus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
void	dda_x_plus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
void	dda_y_minus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
void	dda_y_plus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
void	y_minus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
void	y_plus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
void	x_minus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
void	x_plus(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
void	draw_pixel(t_pixel_info *pixel_info);
void	do_not_draw_pixel(t_pixel_info *pixel_info);

//vector
float	vec2_length(t_v2 *vector);
float	vec3_length(t_v3 *vector);
t_v3	vec3_addition(t_v3 *v0, t_v3 *v1);
t_v2	vec2_addition(t_v2 *v0, t_v2 *v1);
t_v3	vec3_subtract(t_v3 *v0, t_v3 *v1);
t_v2	vec2_subtract(t_v2 *v0, t_v2 *v1);
t_v2	vec2_multiplication(t_v2 *v0, float factor);
t_v3	vec3_multiplication(t_v3 *v0, float factor);
t_v2	vec2_divizion(t_v2 *v0, float factor);
t_v3	vec3_divizion(t_v3 *v0, float factor);

//renderer
char	display(t_w *canvas, char status);

//delay
void	delay(int time_to_wait);
void	do_not_delay(int time_to_wait);

#endif
