/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:02:33 by wbertoni          #+#    #+#             */
/*   Updated: 2021/03/28 18:00:38 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CUB3D_H
# define STRUCT_CUB3D_H


typedef struct s_intxy
{
	int x;
	int y;
} t_intxy;
typedef struct s_sprite
{
	float x;
	float y;
	float distance;
	float angle;
	int visible;
	float height;
	float width;
	float top_y;
	float bottom_y;
	float angle_3d;
	float screen_posx;
	float left_x;
	float right_x;
} t_sprite;

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_player
{
	float		x;
	float		y;
	float		width;
	float		height;
	int			turn_direction;
	int			walk_direction;
	float		rotation_angle;
	float		move_speed;
	float		rotation_speed;
	int			radius;
}				t_player;

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
	t_img *img;
	int width;
	int height;
} t_tex;

typedef struct s_game
{
	t_file *cubfile;
	void *mlx_ptr;
	void *win_ptr;
	int ray_width;
	int bmp;
	t_player *player;
	t_img *frame;
	t_ray **rays;
	t_tex *north;
	t_tex *south;
	t_tex *west;
	t_tex *east;
	t_tex *tex_def;
	t_tex *sprite_tex;
	t_sprite **sprite;
} t_game;

typedef struct	s_point
{
	float		x;
	float		y;
	int			color;
}				t_point;

/*
** Struct to help raycasting(hrc) norminette size
*/
typedef struct	s_hrc
{
	t_point		intercept;
	t_point		step;
}				t_hrc;

#endif
