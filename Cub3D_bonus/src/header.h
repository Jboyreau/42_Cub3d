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
#include <sys/stat.h>
# include "upng.h"

# define MODEL_SCALE 16
# define OBJ_WALL "./obj/wall/wall.obj"
# define MAP_PATH "./map/map.txt"
# define Z_VALUE 0
# define OBJ_FLOOR "./obj/floor/floor.obj"
# define OBJ_ROOF "./obj/roof/roof.obj"
# define TYPE_WALL -1
# define TYPE_FLOOR 3
# define TYPE_ROOF 4
# define TEXTURE_S "./obj/wall/south.png"
# define TEXTURE_N "./obj/wall/north.png"
# define TEXTURE_E "./obj/wall/east.png"
# define TEXTURE_W "./obj/wall/west.png"
# define TEXTURE_F "./obj/floor/floor.png"
# define TEXTURE_R "./obj/roof/roof.png"

# define MUTEX_NUM 17
# define THREAD_NUM 10
# define X_VALUE 0
# define Y_VALUE 2
# define Z_MAX 100
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
# define DIST_INC 0.5
# define ROTATION_INC_PLUS 0.0872665 / 3
# define ROTATION_INC_MINUS -0.0872665 / 3
#define FOG 0xff808080

enum e_cardinal
{
	SOUTH = 0,
	NORTH = 1,
	EAST = 2,
	WEST = 3,
	FLOOR = 4,
	ROOF = 5
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

typedef struct s_color_buffer_point
{
	int			x;
	float		fx;
	int			y;
	float		fy;
	float		z;
	float		inv_z;
	t_tex2		uv;
	t_v3		normal;
}	t_point;

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
	int		texture;
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

typedef struct s_scene
{
	int					nwc;
	int					nwt;
	int					part;
	int					input;
	int					ret;
	int					tex_h[6];
	int					tex_w[6];
	int					t_size[6];
	int					poll_return;
	int					time_to_wait;
	int					previous_frame_time;
	float				scale;
	int					cloud_size;
	int					triangle_index_size;
	int					cloud_size_wall;
	int					triangle_index_size_wall;
	int					cloud_size_floor;
	int					triangle_index_size_floor;
	int					cloud_size_roof;
	int					triangle_index_size_roof;
	int					cloud_size_temp;
	int					triangle_index_size_temp;
	int					poly_size;
	int					inside_size;
	int					nb_tri;
	int					line_len;
	int					line_nb;
	float				pos_incx;
	float				pos_incy;
	float				pos_incz;
	float				dot;
	char				*map;
	char				*obj_path;
	void				*arg;
	int					*color_buffer;
	float				*z_buffer;
	int					*texture[6];
	t_v3_uv				*poly;
	t_v3_uv				*inside_vertices;
	t_v3				*cloud;
	t_tri				*triangle_index;
	t_v3				*cloud_wall;
	t_tri				*triangle_index_wall;
	t_v3				*cloud_floor;
	t_tri				*triangle_index_floor;
	t_v3				*cloud_roof;
	t_tri				*triangle_index_roof;
	t_v3				*cloud_temp;
	t_tri				*triangle_index_temp;
	t_ptri				projected_triangle[10];
	t_f					*fun;
	upng_t				*upng[6];
	pthread_t			thread[THREAD_NUM];
	pthread_spinlock_t	*fast_lock;
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
	int					texture;
	int					rdy;
	int					finish;
	int					call;
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
	float				inv_sloap_2_factor;
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
	pthread_spinlock_t	*fast_lock;
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
int		assemble_map(t_scene *scene);

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
void	dot(t_pixel_info *pixel_info);

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
char	load_texture(char *file, t_scene *scene, int cardinal);

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
