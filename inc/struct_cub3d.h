/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:02:33 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/21 09:48:28 by wbertoni         ###   ########.fr       */
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

typedef struct s_game
{
	t_file *cubfile;
	void *mlx_ptr;
	void *win_ptr;
	t_player *player;
	t_img *frame;
} t_game;

typedef struct	s_point
{
	float		x;
	float		y;
	int			color;
}				t_point;

#endif
