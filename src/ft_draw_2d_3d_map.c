/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_2d_3d_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:50:15 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/04 14:10:50 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_draw_wall(t_vars *vars, t_data *img, float wall_height,
						 int index)
{
	int color;
	int i;
	int j;
	int y;

	i = 0;
	j = 0;
	y = vars->rays[index]->wall_top;
	while (i < WALL_STRIP_WIDTH)
	{
		while (j < vars->rays[index]->wall_bottom - vars->rays[index]->wall_top)
		{
			color = ft_get_texture_color(vars, wall_height, index, y);
			my_mlx_pixel_put(img, (index * WALL_STRIP_WIDTH) + i,
							 vars->rays[index]->wall_top + j, color);
			y++;
			j++;
		}
		y = vars->rays[index]->wall_top;
		j = 0;
		i++;
	}
}

static void ft_draw_ceiling(t_vars *vars, t_data *img, int index)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (vars->rays[index]->wall_top > 0)
	{
		while (i < WALL_STRIP_WIDTH)
		{
			while (j < vars->rays[index]->wall_top)
			{
				my_mlx_pixel_put(img, (index * WALL_STRIP_WIDTH) + i, j,
								 vars->file->ceiling);
				j++;
			}
			j = 0;
			i++;
		}
	}
}

static void ft_draw_floor(t_vars *vars, t_data *img, int index)
{
	int i;
	int j;

	i = 0;
	j = vars->rays[index]->wall_bottom;
	if (vars->rays[index]->wall_top > 0)
	{
		while (i < WALL_STRIP_WIDTH)
		{
			while (j < vars->win_height)
			{
				my_mlx_pixel_put(img, (index * WALL_STRIP_WIDTH) + i, j,
								 vars->file->floor);
				j++;
			}
			j = 0;
			i++;
		}
	}
}

void		ft_draw_3d_map(t_vars *vars, t_data *img)
{
	float	player_distance;
	float	wall_height;
	float	perpDistance;
	int		i;

	i = 0;
	player_distance = (vars->win_width / 2) / tan(ft_degtorad(FOV_ANGLE / 2));
	while (i < (vars->win_width / WALL_STRIP_WIDTH))
	{
		perpDistance = vars->rays[i]->distance * cos(vars->rays[i]->ray_angle - vars->player->rotation_angle);
		wall_height = (TILE_SIZE / perpDistance) * player_distance;
		vars->rays[i]->wall_top = (vars->win_height / 2) - (wall_height / 2);
		vars->rays[i]->wall_top = (vars->rays[i]->wall_top < 0) ? 0
		: vars->rays[i]->wall_top;
		vars->rays[i]->wall_bottom = (vars->win_height / 2) + (wall_height / 2);
		vars->rays[i]->wall_bottom = (vars->rays[i]->wall_bottom
		> vars->win_height) ? vars->win_height : vars->rays[i]->wall_bottom;
		ft_draw_ceiling(vars, img, i);
		ft_draw_wall(vars, img, wall_height, i);
		ft_draw_floor(vars, img, i);
		i++;
	}
}

void		ft_draw_2d_map(t_vars *vars, t_data *img)
{
	int		i;
	t_point central;
	t_point end;

	i = 0;
	central = ft_create_point(MINIMAP_SCALE_FACTOR * vars->player->x,
							  MINIMAP_SCALE_FACTOR * vars->player->y,
							  0x00ff0000);
	ft_create_2d_map(img, vars->map);
	ft_circle_filled(img, central, vars->player->radius);
	while (i < (vars->win_width / WALL_STRIP_WIDTH))
	{
		end = ft_create_point(MINIMAP_SCALE_FACTOR * vars->rays[i]->wall_hit_x,
							  MINIMAP_SCALE_FACTOR * vars->rays[i]->wall_hit_y,
							  0x00ff0000);
		ft_line_dda(img, central, end);
		i++;
	}
}
