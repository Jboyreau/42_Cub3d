#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <SDL2/SDL.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include "upng.h"

# define OBJ "./obj/level/level.obj"
 # define Z_VALUE 10//level
 # define TEXTURE "./obj/text/mossystone.png"

//# define OBJ "./obj/cow/cow.obj"
//# define Z_VALUE 2//cow
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/cube/cube.obj"
//# define Z_VALUE 10//cube
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/f22/f22.obj"
//# define Z_VALUE 5//f22
//# define TEXTURE "./obj/f22/f22.png"

//# define OBJ "./obj/f117/f117.obj"
//# define Z_VALUE 5//f117
//#define TEXTURE "./obj/f117/f117.png"

//# define OBJ "./obj/drone/drone.obj"
//# define Z_VALUE 5//drone
//#define TEXTURE "./obj/drone/drone.png"

//# define OBJ "./obj/crab/crab.obj"
//# define Z_VALUE 5//crab
//#define TEXTURE "./obj/crab/crab.png"

//# define OBJ "./obj/sphere/sphere.obj"
//# define Z_VALUE 5//sphere
//# define TEXTURE "./obj/sphere/pikuma.png"

//# define OBJ "./obj/big_cub/big_cub.obj"
//# define Z_VALUE 3//big_cube
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/floor/floor.obj"
//# define Z_VALUE 2//floor
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/assault_rifle/AssaultRifle.obj"
//# define Z_VALUE 2//AssaultRifle
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/famas/famas.obj"
//# define Z_VALUE 2//famas
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/egg_bot/egg_bot.obj"
//# define Z_VALUE 2//egg_bot
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/naruto/naruto.obj"
//# define Z_VALUE 2//naruto
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/cyberman/cyberman.obj"
//# define Z_VALUE 2//cyberman
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/monument_alexender/monument_alexender.obj"
//# define Z_VALUE 2//monument_alexender
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/sword/sword.obj"
//# define Z_VALUE 2//sword
//#define TEXTURE "./obj/sword/wood.png"

//# define OBJ "./obj/bear/bear.obj"
//# define Z_VALUE 2//bear
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/dragon/dragon.obj"
//# define Z_VALUE 2//dragon
//#define TEXTURE "./obj/texture.png"

//# define OBJ "./obj/terrain/terrain.obj"
//# define Z_VALUE 1//terrain
//#define TEXTURE "./obj/text/mossystone.png"

# define MUTEX_NUM 17
# define THREAD_NUM 10
# define X_VALUE 0
# define Y_VALUE 0.5
# define Z_MAX 30
# define Z_MIN 1
# define FPS 60
# define FRAME_TARGET_TIME (1000 / FPS)
# define SCALE 1000
# define SCALE_INC 15
# define HEIGHT 720
# define WIDTH 1280
# define BUFF_SIZE 921600 //HEIGHT * WIDTH
# define CLEAR_SIZE 460800 //(HEIGHT * WIDTH) / 2
# define POLY_SIZE 10
# define MIDLE_X 640
# define MIDLE_Y 360
# define DIST_INC 0.2
# define ROTATION_INC_PLUS 0.0872665 / 3
# define ROTATION_INC_MINUS -0.0872665 / 3

enum e_mutex_name
{
	INTER_THREAD = 16,
};

typedef struct s_canvas
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				*color_buffer;
	SDL_Texture		*color_buffer_texture;
}	t_w;

typedef struct s_uv_coordinate
{
	float	u;
	float	v;
	float	w;
}	t_tex3;

typedef struct s_texture
{
	float	u;
	float	v;
}	t_tex2;

typedef struct s_affine
{
	float	a;
	float	b;
}	t_aff;

typedef struct s_color_buffer_point
{
	int			x;
	float		fx;
	int			y;
	float		fy;
	float		z;
	float		inv_z;
	t_tex2		uv;
}	t_point;

typedef struct s_2dvector
{
	float		x;
	float		y;
}	t_v2;

typedef struct s_3dvector
{
	float		x;
	float		y;
	float		z;	
	float		inv_z;
}	t_v3;

typedef struct s_3dvector_uv
{
	float		x;
	float		y;
	float		z;
	float		u;
	float		v;
}	t_v3_uv;

typedef struct s_barycentric_reference
{
	t_v2 ap;
	t_v2 pc;
	t_v2 pb;
}	t_br;

typedef struct s_line
{
	t_v3_uv	vec_cur;
	t_v3_uv	vec_prev;
	t_v3_uv	*cur;
	t_v3_uv	*prev;
}	t_line;

typedef struct s_camera
{
	t_v3	position;
	t_v3	rotation;
	float	fov_h;
	float	fov_w;
}	t_cam;

typedef struct s_funarrays	t_f;

typedef struct s_tirangle
{
	int		a;
	int		b;
	int		c;
	t_tex2	uv_a;
	t_tex2	uv_b;
	t_tex2	uv_c;
}	t_tri;

typedef struct s_projected_tirangle
{
	t_v3	a;
	t_v3	b;
	t_v3	c;
	t_point	p0;
	t_point	p1;
	t_point	p2;
}	t_ptri;

typedef struct s_plan
{
	t_v3_uv	point;
	t_v3_uv	n;
}	t_plane;

typedef struct s_view
{
	t_plane	left;
	t_plane	right;
	t_plane	top;
	t_plane	bottom;
	t_plane	near;
	t_plane	far;
}	t_view;

typedef struct s_scene //what I project
{
	int					input;
	int					ret;
	int					tex_h;
	int					tex_w;
	int					t_size;
	int					poll_return;
	int						time_to_wait;
	int					previous_frame_time;
	float				scale;
	int					cloud_size;
	int					triangle_index_size;
	int					poly_size;
	int					inside_size;
	int					nb_tri;
	float				pos_incx;
	float				pos_incy;
	float				pos_incz;
	float				dot;
	void				*arg;
	int					*color_buffer;
	float				*z_buffer;
	int					*texture;
	t_v3_uv				*poly;
	t_v3_uv				*inside_vertices;
	t_v3				*cloud;
	t_v3				*cloud_save;
	t_tri				*triangle_index;
	t_ptri				*projected_triangle;
	t_f					*fun;
	upng_t				*upng;
	pthread_barrier_t	*first_wall;
	pthread_barrier_t	*wait_triangle;
	pthread_barrier_t	*start_transform;	
	pthread_barrier_t	*wait_transform;
	pthread_mutex_t 	code_mutex[MUTEX_NUM];
	pthread_t			thread[THREAD_NUM];
	pthread_t			thread_transform[THREAD_NUM];
	t_v3				rotation;
	t_v3				origin;
	t_cam				camera;
	t_view				view;
}	t_scene;

typedef struct t_keys
{
	int		key;
	int		wheel;
	int		mouse_wheel_event;
}	t_keys;

typedef struct s_pixel_info
{
	char				first;
	int					condition;
	int					cell;
	int					color;
	int					y;
	int					y_start;
	int					y_end;
	int					len_y;
	int					len_y_bottom;
	int					len_y_top;
	int					ratio;
	int					modulo;
	float				inv_sloap_2;
	float				depth;
	float				para_abc;
	float				p0_itu;
	float				p1_itu;
	float				p2_itu;
	float				p0_itv;
	float				p1_itv;
	float				p2_itv;
	float				dot;
	t_scene				*scene;
	pthread_barrier_t	*wait_triangle;
	pthread_barrier_t	*wait_main_lock;
	pthread_barrier_t	*first_wall;
	t_v2				a;
	t_v2				b;
	t_v2				c;
	t_v2				p;
	t_v2				ac;
	t_v2				ab;
	t_aff				line_equation_01;
	t_aff				line_equation_02;
	t_aff				line_equation_12;
	t_v3				weight;
	t_v3				weight_start;
	t_v3				weight_end;
	t_v3				screen_space_origin;
	t_v3				screen_space_p;
	t_tex3				interpolated;
	t_tex3				interpolated_start;
	t_tex3				interpolated_end;
	t_point				p_start;
	t_point				p_end;
	t_point				p0;
	t_point				p1;
	t_point				p2;
	t_point				screen_space_p0;
	t_point				screen_space_p1;
	t_point				screen_space_p2;	
}	t_pixel_info;

typedef struct s_fun_start_argument
{
	t_pixel_info pixel_info;
}	t_arg;

typedef struct s_dda
{
	int		delta_x;
	int		delta_y;
	int		abs_delta_x;
	int		abs_delta_y;
	t_v3	p1;
	t_v3	p2;	
}	t_dda;

struct s_funarrays
{
	char	(*fun_update[65537])(t_scene *);
	int		(*fun_event[128])(t_keys *);
	void	(*fun_draw_pixel[128])(t_pixel_info *);
	void	(*fun_draw_pixel2[128])(t_pixel_info *);
	void	(*fun_draw_pixel_last[128])(t_pixel_info *);
	void	(*fun_draw_pixel_last2[128])(t_pixel_info *);
	void	(*fun_delay[128])(int);
	void	(*dda[128])(t_scene *scene, t_pixel_info *pixel_info, t_dda *dda);
	void	(*culling[128])(t_scene *scene, int i, t_pixel_info *pixel_info);
	void	(*draw_ft[128])(t_pixel_info *t_pixel_info, int i);
	void	(*flat_top_or_bottom[128])(t_pixel_info *info, t_point *p0, t_point *p1, t_point *p2, int thread_index);
	void	(*start_draw_ft[128])(t_scene *scene, t_pixel_info *pixel_info, int i);
	void	(*inter[128])(t_scene *scene, t_line *cp, t_v2 *dot, t_v3_uv *inside_vertices);
};

//point cloud generation
char	populate_3d_space(t_scene *scene);

//init
void	initialize_fun(t_f *fun);
t_scene	*initialize_scene(int *color_buffer, t_f *fun);

//process input
int		process_input(int (*fun_event[])(t_keys *), t_scene *scene);
int		set_nothing(t_keys *keys);
int		set_quit(t_keys *keys);
int		set_index(t_keys *keys);

//update / projection
//void	clear_color_buffer(int *color_buffer);
void	clear_color_buffer(long long int *color_buffer, float *z_buffer);
char	nothing(t_scene *scene);
char	quit(t_scene *scene);
//char 	ortho_project(t_scene *scene);
//char 	ortho_project_zoom_plus(t_scene *scene);
//char 	ortho_project_zoom_minus(t_scene *scene);
void	triangle_to_color_buffer(t_scene *scene, int i, t_pixel_info *pixel_info);
void	triangle_to_nowhere(t_scene *scene, int i, t_pixel_info *pixel_info);
char	perspective_project_zoom_plus(t_scene *scene);
char	perspective_project_zoom_minus(t_scene *scene);
char	perspective_project(t_scene *scene);
char	camera_perspective_project(t_scene *scene);
char	perspective_project_close(t_scene *scene);
char	perspective_project_far(t_scene *scene);
char	perspective_project_down(t_scene *scene);
char	perspective_project_up(t_scene *scene);
char	perspective_project_right(t_scene *scene);
char	perspective_project_left(t_scene *scene);
void	launch(t_scene *scene, t_pixel_info *pixel_info, int i);
void	dont_launch(t_scene *scene, t_pixel_info *pixel_info, int i);

//linear transform
void	rotation_x(t_scene *scene, float angle);
char	camera_rotation_x_minus(t_scene *scene);
char	camera_rotation_x_plus(t_scene *scene);
char	camera_rotation_y_minus(t_scene *scene);
char	camera_rotation_y_plus(t_scene *scene);
char	rotation_x_minus(t_scene *scene);
char	rotation_x_plus(t_scene *scene);
char	rotation_y_minus(t_scene *scene);
char	rotation_y_plus(t_scene *scene);
char	rotation_z_plus(t_scene *scene);
char	rotation_z_minus(t_scene *scene);
void	rev_camera_rotation_x(t_scene *scene, int i, float angle);
void	rev_camera_rotation_origin_x(t_v3 *camera_position, float angle);

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
void	draw_pixel2(t_pixel_info *pixel_info);
void	draw_pixel_last(t_pixel_info *pixel_info);
void	draw_pixel_last2(t_pixel_info *pixel_info);
void	draw_first_pixel(t_pixel_info *pixel_info);
void	do_not_draw_pixel(t_pixel_info *pixel_info);
void	dot_p20(t_pixel_info *pixel_info);

//triangle filling
void	draw_ft012(t_pixel_info *pixel_info, int i);
void	draw_ft021(t_pixel_info *pixel_info, int i);
void	draw_ft102(t_pixel_info *pixel_info, int i);
void	draw_ft120(t_pixel_info *pixel_info, int i);
void	draw_ft201(t_pixel_info *pixel_info, int i);
void	draw_ft210(t_pixel_info *pixel_info, int i);
void	flat_bottom_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index);
void	flat_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index);
void	flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index);
void	nothing_tb(t_pixel_info *pixel_info, t_point *p0, t_point *p1, t_point *p2, int thread_index);

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
t_v3	vec3_cross(t_v3 *a, t_v3 *b);
float	vec2_dot(t_v2 *a, t_v2 *b);
float	vec3_dot(t_v3 *a, t_v3 *b);
void	vec3_normalize(t_v3 *vec);
void	vec2_normalize(t_v2 *vec);
float	vec3_normalize_r(t_v3 *vec);
void	vec3_denormalize(t_v3 *vec, float len);
t_v3_uv	vec3uv_multiplication(t_v3_uv *v0, float factor);
t_v3_uv	vec3uv_addition(t_v3_uv *v0, t_v3_uv *v1);
t_v3_uv	vec3uv_subtract(t_v3_uv *v0, t_v3_uv *v1);
float	vec3uv_dot(t_v3_uv *a, t_v3_uv *b);

//back_face_culling
float	is_visible(t_scene *scene, int i);

//texture
char	load_texture(char *file, t_scene *scene);

//Clipping
void	uv_tv3(t_v3 *b, t_v3_uv *a);
void	tv3_uv(t_v3_uv *b, t_v3 *a);
t_v3_uv	*tri_to_poly(t_scene *scene, t_tri *face);
void	poly_to_tri(t_scene *scene, t_v3_uv *poly);
void	inter_p_outside(t_scene *scene, t_line *cp, t_v2 *dot, t_v3_uv *inside_vertices);
void	inter_c_outside(t_scene *scene, t_line *cp, t_v2 *dot, t_v3_uv *inside_vertices);
void	inter_both_inside(t_scene *scene, t_line *cp, t_v2 *dot, t_v3_uv *inside_vertices);
void	inter_both_outside(t_scene *scene, t_line *cp, t_v2 *dot, t_v3_uv *inside_vertices);

//renderer
char	display(t_w *canvas, char status);

//delay
void	delay(int time_to_wait);
void	do_not_delay(int time_to_wait);

//threads
void			init_threads(t_scene *scene);
void			*start(void *arg);
#endif
