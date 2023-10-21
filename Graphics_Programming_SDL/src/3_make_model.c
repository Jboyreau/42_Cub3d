#include <SDL2/SDL.h>
#include <stdio.h>
#include "header.h"

static void make_triangle_index(t_tri *triangle_index)
{
	//front
	(*triangle_index).a = 1; (*triangle_index).b = 2; (*triangle_index).c = 3;
	(*(triangle_index + 1)).a = 1; (*(triangle_index + 1)).b = 3; (*(triangle_index + 1)).c = 4;
	//right
	(*(triangle_index + 2)).a = 4; (*(triangle_index + 2)).b = 3; (*(triangle_index + 2)).c = 5;
	(*(triangle_index + 3)).a = 4; (*(triangle_index + 3)).b = 5; (*(triangle_index + 3)).c = 6;
	//back
	(*(triangle_index + 4)).a = 6; (*(triangle_index + 4)).b = 5; (*(triangle_index + 4)).c = 7;
	(*(triangle_index + 5)).a = 6; (*(triangle_index + 5)).b = 7; (*(triangle_index + 5)).c = 8;
	//left
	(*(triangle_index + 6)).a = 8; (*(triangle_index + 6)).b = 7; (*(triangle_index + 6)).c = 2;
	(*(triangle_index + 7)).a = 8; (*(triangle_index + 7)).b = 2; (*(triangle_index + 7)).c = 1;
	//top
	(*(triangle_index + 8)).a = 2; (*(triangle_index + 8)).b = 7; (*(triangle_index + 8)).c = 5;
	(*(triangle_index + 9)).a = 2; (*(triangle_index + 9)).b = 5; (*(triangle_index + 9)).c = 3;
	//botom
	(*(triangle_index + 10)).a = 6; (*(triangle_index + 10)).b = 8; (*(triangle_index + 10)).c = 1;
	(*(triangle_index + 11)).a = 6; (*(triangle_index + 11)).b = 1; (*(triangle_index + 11)).c = 4;
}

static void make_cloud(t_v3 *cloud)
{
	(*cloud).x = -1; (*cloud).y = -1; (*cloud).z = -1; //1
	(*(cloud + 1)).x = -1; (*(cloud + 1)).y = 1; (*(cloud + 1)).z = -1; //2
	(*(cloud + 2)).x = 1; (*(cloud + 2)).y = 1; (*(cloud + 2)).z = -1; //3
	(*(cloud + 3)).x = 1; (*(cloud + 3)).y = -1; (*(cloud + 3)).z = -1; //4
	(*(cloud + 4)).x = 1; (*(cloud + 4)).y = 1; (*(cloud + 4)).z = 1; //5
	(*(cloud + 5)).x = 1; (*(cloud + 5)).y = -1; (*(cloud + 5)).z = 1; //6
	(*(cloud + 6)).x = -1; (*(cloud + 6)).y = 1; (*(cloud + 6)).z = 1; //7
	(*(cloud + 7)).x = -1; (*(cloud + 7)).y = -1; (*(cloud + 7)).z = 1; //8
}

void	populate_3d_space(t_v3 *cloud, t_tri *triangle_index)
{
	make_cloud(cloud);
	make_triangle_index(triangle_index);
}
