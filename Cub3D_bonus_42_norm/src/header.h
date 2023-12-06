/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:00:05 by jboyreau          #+#    #+#             */
/*   Updated: 2023/12/07 00:13:58 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>
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
# define Y_VALUE 3
# define Z_MAX 150
# define Z_MIN 1
# define FPS 60
# define SCALE 1000
# define SCALE_INC 15
# define HEIGHT 720
# define WIDTH 1280
# define BUFF_SIZE 921600
# define CLEAR_SIZE 460800
# define POLY_SIZE 10
# define MIDLE_X 640
# define MIDLE_Y 360
# define DIST_INC 0.5
# define ROTATION_INC_PLUS 0.02908883
# define ROTATION_INC_MINUS -0.02908883

enum e_cardinal
{
	SOUTH = 0,
	NORTH = 1,
	EAST = 2,
	WEST = 3,
	FLOOR = 4,
	ROOF = 5
};

typedef struct s_index
{
	int	i;
	int	j;
	int	index;
}	t_index;

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
	t_v2	ap;
	t_v2	pc;
	t_v2	pb;
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
	char				card;
	int					px;
	int					pz;
	int					wall_last_index;
	int					nwc;
	int					nwt;
	int					part;
	int					input;
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
	char				tno[100];
	char				tso[100];
	char				tea[100];
	char				twe[100];
	char				tf[100];
	char				tr[100];
	char				*map_path;
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
	int					thread_index;
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
	t_pixel_info	pixel_info;
}	t_arg;

struct s_funarrays
{
	char	(*fun_update[65537])(t_scene *);
	int		(*fun_event[128])(t_keys *);
	void	(*fun_draw_pixel[128])(t_pixel_info *);
	void	(*culling[128])(t_scene *scene, int i, t_pixel_info *pixel_info);
	void	(*draw_ft[128])(t_pixel_info *t_pixel_info, int i);
	void	(*flat_top_or_bottom[128])(t_pixel_info *info, t_point *p0,
			t_point *p1, t_point *p2);
	void	(*start_draw_ft[128])(t_scene *scene,
			t_pixel_info *pixel_info, int i);
	void	(*inter[128])(t_scene *scene, t_line *cp, t_v2 *dot,
			t_v3_uv *inside_vertices);
};

//point cloud generation
char	populate_3d_space(t_scene *scene);
int		make_triangle_index(t_tri *triangle_index, char *obj,
			t_tex2 *vt, int part);
void	make_vt(char *obj, t_tex2 *vt);
char	check_material(char *str);
int		assemble_map(t_scene *scene);

//init
void	initialize_fun(t_f *fun);
void	initialize_culling(void (*culling[])(t_scene *scene, int i,
				t_pixel_info *pixel_info));
void	initialize_start_draw_ft(void (*start_draw_ft[])(t_scene *scene,
				t_pixel_info *pixel_info, int i));
void	initialize_draw_ft(void (*draw_ft[])
			(t_pixel_info *t_pixel_info, int i));
void	initialize_flat_top_or_bottom(void (*flat_top_or_bottom[])
			(t_pixel_info *info, t_point *p0, t_point *p1, t_point *p2));
void	initialize_inter(void (*inter[])(t_scene *scene, t_line *cp,
				t_v2 *dot, t_v3_uv *inside_vertices));
//init map
int		is_valid(t_scene *scene);
int		check_left(t_scene *scene, int px, int pz);
int		check_right(t_scene *scene, int px, int pz);
int		check_up(t_scene *scene, int px, int pz);
int		check_down(t_scene *scene, int px, int pz);
int		check_uright(t_scene *scene, int px, int pz);
int		check_uleft(t_scene *scene, int px, int pz);
int		check_dright(t_scene *scene, int px, int pz);
int		check_dleft(t_scene *scene, int px, int pz);
int		count_player(t_scene *scene);
int		check_garbage(t_scene *scene);
int		check_error(t_scene *scene, int px, int pz);
int		check_lim(t_scene *scene, int px, int pz);
int		flood_fill(t_scene *scene, int px, int pz);
int		get_texture(t_scene *scene, char *map_raw);
void	write_tex_end(t_scene *scene, int index, int j);
void	write_tex(char *map_raw, t_scene *scene, int index, int j);
void	assemble(t_scene *scene);
void	assemble_wall(t_scene *scene, int l, int c);
void	paste_roof(t_scene *scene, int z, int x, int n);
void	paste_floor(t_scene *scene, int z, int x, int n);
int		process_map(t_scene *scene, char *map_raw, int line_len,
			int line_nb);
void	set_map_size(char *map_raw, int *line_len, int *line_nb);
char	*load_map(char *file, int fd, int len, char *buffer);
void	d(t_scene *scene, char *map_raw);


t_scene	*initialize_scene(t_f *fun, char *map_path);
void	affect_wall(t_scene *scene);
void	affect_floor(t_scene *scene);
void	affect_roof(t_scene *scene);
void	init_plane(t_scene *scene);
void	init_camera(t_scene *scene);

//process input
int		process_input(int (*fun_event[])(t_keys *), t_scene *scene);
int		set_nothing(t_keys *keys);
int		set_quit(t_keys *keys);
int		set_index(t_keys *keys);

//update / projection
void	clear_color_buffer(long long int *color_buffer, float *z_buffer);
char	nothing(t_scene *scene);
char	quit(t_scene *scene);
void	triangle_to_color_buffer(t_scene *scene, int i,
			t_pixel_info *pixel_info);
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
void	rotation_y(t_scene *scene, float angle);
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
void	draw_per_tri_shading(t_pixel_info *pixel_info);
void	draw_per_pixel_shading(t_pixel_info *pixel_info);
void	do_not_draw_pixel(t_pixel_info *pixel_info);
void	dot(t_pixel_info *pixel_info);
t_v3	calcultate_interpolated_normal(t_pixel_info *pixel_info);
t_v3	init_face(t_v2 *a, float az);

//triangle filling
void	draw_ft012(t_pixel_info *pixel_info, int i);
void	draw_ft021(t_pixel_info *pixel_info, int i);
void	draw_ft102(t_pixel_info *pixel_info, int i);
void	draw_ft120(t_pixel_info *pixel_info, int i);
void	draw_ft201(t_pixel_info *pixel_info, int i);
void	draw_ft210(t_pixel_info *pixel_info, int i);
void	flat_bottom_top(t_pixel_info *pixel_info, t_point *p0,
			t_point *p1, t_point *p2);
void	flat_top(t_pixel_info *pixel_info, t_point *p0, t_point *p1,
			t_point *p2);
void	flat_bottom(t_pixel_info *pixel_info, t_point *p0, t_point *p1,
			t_point *p2);
void	nothing_tb(t_pixel_info *pixel_info, t_point *p0, t_point *p1,
			t_point *p2);

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
void	inter_p_outside(t_scene *scene, t_line *cp, t_v2 *dot,
			t_v3_uv *inside_vertices);
void	inter_c_outside(t_scene *scene, t_line *cp, t_v2 *dot,
			t_v3_uv *inside_vertices);
void	inter_both_inside(t_scene *scene, t_line *cp, t_v2 *dot,
			t_v3_uv *inside_vertices);
void	inter_both_outside(t_scene *scene, t_line *cp, t_v2 *dot,
			t_v3_uv *inside_vertices);

//renderer
void	display(t_w *canvas, t_scene *scene);

//threads
void	init_threads(t_scene *scene);
void	*start(void *arg);

//destroy
void	destroy(SDL_Window *window, SDL_Renderer *renderer, t_scene *scene,
			SDL_Texture *color_buffer_texture);
void	kill_all_threads(t_scene *scene);
#endif
