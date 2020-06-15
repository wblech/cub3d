/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:33:46 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/15 00:32:55 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "get_next_line.h"
#include "../libft/libft.h"
// #include <unistd.h>
// #include <limits.h>
#include <math.h>
#include "mlx.h"
#include <stdio.h> // verificar necessidade
// #include <stdlib.h> // precisa recriar a funcao abs
#include <string.h>
#include <errno.h>

#define ROUND(a) ((int)(a + 0.5)) //proibido
#ifndef TILE_SIZE
#define TILE_SIZE 64
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419716939937510582097494459
#endif
#ifndef FOV_ANGLE
#define FOV_ANGLE 60
#endif
#ifndef WALL_STRIP_WIDTH
#define WALL_STRIP_WIDTH 1
#endif
#define NORTH 3 * M_PI / 2
#define SOUTH M_PI / 2
#define WEST M_PI
#define EAST 0
#define KEY_W 0x0077
#define KEY_S 0x0073
#define KEY_A 0x0061
#define KEY_D 0x0064
#define KEY_ESC 0xff1b
#define KEY_M 0x006d
#define ARROW_LEFT 0xff51
#define ARROW_RIGHT 0xff53
#define TRUE 1
#define FALSE 0
#define MINIMAP_SCALE_FACTOR 0.2

int g_minimap;
// int TILE_SIZE;

typedef enum e_error
{
	noerror,
	eallow,
	enull,
	ewall,
	eempty,
	erespos,
	eresarg,
	epathtex,
	ecolortex,
	ergbsize,
	enores,
	enotexture,
	enocolor,
	enomap,
	eplayer,
} t_error;

t_error g_error;

typedef enum e_face
{
	up,
	down,
	left,
	right
} t_face;

typedef enum e_side
{
	north,
	south,
	west,
	east
} t_side;

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_point
{
	float x;
	float y;
	int color;
} t_point;

typedef struct s_map // criar função que le e cria a estrutura
{
	int num_row;
	int num_col;
	char initial_pl_cardinal;
	int initial_pl_x;
	int initial_pl_y;
	char **map;
} t_map;

typedef struct s_player
{
	float x;
	float y;
	int radius;
	int turn_direction;
	int walk_direction;
	float rotation_angle;
	float move_speed;
	float rotatio_speed;
} t_player;

typedef struct s_ray
{
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	float ray_angle;
	float wall_top;
	float wall_bottom;
	int was_wall_hit_vertical;
} t_ray;

typedef struct s_tex
{
	t_data *img;
	int width;
	int height;
} t_tex;

typedef struct s_file
{
	int width;
	int height;
	t_tex *north;
	t_tex *south;
	t_tex *west;
	t_tex *east;
	t_tex *sprite;
	int floor;
	int ceiling;
	t_map *map;
} t_file;

typedef struct s_vars
{
	void *mlx;
	void *win;
	int win_width;
	int win_height;
	t_data *img;
	t_map *map;
	t_player *player;
	t_ray **rays;
	t_tex *texture;
	t_file *file;
} t_vars;

/*Utils*/
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_point ft_create_point(float x, float y, int color);
float ft_degtorad(float degree);

/*Color Management*/

int create_trgb(int t, int r, int g, int b);
int get_t(int trgb);
int get_r(int trgb);
int get_g(int trgb);
int get_b(int trgb);
int add_shades(double dst, int color);
int get_opposite(int color);
int get_color(t_point current, t_point start, t_point end);

/*Draw a line*/
void ft_line(t_data *img, t_point start, t_point end);
void ft_line_dda(t_data *img, t_point start, t_point end);
void ft_hline(t_data *img, t_point start, int size);

/*Simple Shapes*/
void ft_circle_polar(t_data *img, t_point pos, int radians);
void ft_circle(t_data *img, t_point center, int r);
void ft_circle_filled(t_data *img, t_point center, int r);
void ft_rect(t_data *img, t_point start, t_point size);
void ft_rect_filled(t_data *img, t_point start, t_point size);
void ft_rect_filled_borderless(t_data *img, t_point start, t_point size);

/* Player Functions */
t_player *ft_create_player(t_vars *vars, char cardinal, float speed);

/* Game */
int ft_render(t_vars *vars);
/* win_update.c */
int ft_close(t_vars *vars);
int ft_update_press(int keycode, t_vars *vars);
int ft_update_release(int keycode, t_vars *vars);
/* ft_vars.c */
int ft_create_vars(t_vars *vars, t_map *map, char *path);
void ft_del_vars(t_vars *vars);
/* ft_image.c */
t_data *ft_create_image(void *mlx_ptr, int x, int y);
void ft_destroy_free_set_img(t_vars *vars, t_data *new_img);
/* ft_map.c */
void ft_create_2d_map(t_data *img, t_map *map);
void ft_free_map(char **map);
int ft_has_wall(t_vars *vars, int x, int y);
void ft_check_collision(t_vars *vars);

int ft_render(t_vars *vars);
// void ft_create_rays(t_vars *vars);
// void ft_raycast_render(t_vars *vars, t_data *img);
int ft_raycast(t_vars *vars);
void ft_draw_2d_map(t_vars *vars, t_data *img);
int is_end_window(t_vars *vars, float x, float y);
void ft_draw_3d_map(t_vars *vars, t_data *img);
float ft_normalize_angle(float angle);
int ft_calc_facing(float ray_angle, t_face face);
float ft_distance_between_points(t_point start, t_point end);
void ft_del_rays(t_vars *vars);
t_tex *ft_create_texture(void *mlx_ptr, char *path);
int ft_get_texture_color(t_vars *vars, float wall_height, int index, int y);
char **ft_malloc_map(int row, int col);
int ft_is_wall_or_space(int c);
void ft_print_error(t_error error);
t_file *ft_cubfile(t_vars *vars, char *cubfile);
int ft_check_map_cubfile_has_empty_line(char **line);
t_error ft_check_map_cubfile(t_map *map);
t_error ft_get_map_cubfile(t_file *file, char *line);
t_error ft_get_info_value(t_vars *vars, t_file *file, char **info);
t_file *ft_cubfile(t_vars *vars, char *cubfile);
int ft_cubfile_check_and_get_function(t_file *file);
t_error ft_get_cubfile_value(t_vars *vars, t_file *file, char *line);
t_error ft_malloc_file_map(t_file *file);




#endif
