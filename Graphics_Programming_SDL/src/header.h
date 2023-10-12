#ifndef HEADER_H
#define HEADER_H
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

//init
void	initialize_fun_event(int (*fun_event[])(int));
void	initialize_fun_key_triggered(char (*fun[])(int *));

//process input
int		process_input(int (*fun_event[])(int));
int		set_nothing(int key);
int		set_quit(int key);
int		set_index(int key);

//update
void	clear_color_buffer(long long int *color_buffer);
char	nothing(int *color_buffer);
char	quit(int *color_buffer);
char	square(int *color_buffer);
char	circle(int *color_buffer);

//renderer
char	display(t_w *canvas, char status);

#endif
