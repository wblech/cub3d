/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:02:33 by wbertoni          #+#    #+#             */
/*   Updated: 2020/12/26 13:33:00 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CUB3D_H
# define STRUCT_CUB3D_H

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
typedef struct s_game
{
	t_file *cubfile;
	void *mlx_ptr;
	void *win_ptr;
	int ray_width;
	t_player *player;
	t_img *frame;
	t_ray **rays;
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
typedef struct	hrc
{
	t_point		intercept;
	t_point		step;
}				t_hrc;

#endif
