/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_3d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:38:27 by wbertoni          #+#    #+#             */
/*   Updated: 2021/01/04 18:22:30 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_draw_wall(t_game *game, t_img *img, float wall_height,
						int index)
{
	int color;
	int i;
	int j;
	int y;

	i = 0;
	j = 0;
	y = game->rays[index]->wall_top;
	while (i < WALL_STRIP_WIDTH)
	{
		while (j < game->rays[index]->wall_bottom - game->rays[index]->wall_top)
		{
			color = ft_get_texture_color(game, wall_height, index, y);
			my_mlx_pixel_put(img, (index * WALL_STRIP_WIDTH) + i,
							game->rays[index]->wall_top + j, color);
			y++;
			j++;
		}
		y = game->rays[index]->wall_top;
		j = 0;
		i++;
	}
}

static void		ft_draw_ceiling(t_game *game, t_img *img, int index)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (game->rays[index]->wall_top > 0)
	{
		while (i < WALL_STRIP_WIDTH)
		{
			while (j < game->rays[index]->wall_top)
			{
				my_mlx_pixel_put(img, (index * WALL_STRIP_WIDTH) + i, j,
								game->cubfile->ceiling);
				j++;
			}
			j = 0;
			i++;
		}
	}
}

static void		ft_draw_floor(t_game *game, t_img *img, int index)
{
	int i;
	int j;

	i = 0;
	j = game->rays[index]->wall_bottom;
	if (game->rays[index]->wall_top > 0)
	{
		while (i < WALL_STRIP_WIDTH)
		{
			while (j < game->cubfile->height)
			{
				my_mlx_pixel_put(img, (index * WALL_STRIP_WIDTH) + i, j,
								game->cubfile->floor);
				j++;
			}
			j = 0;
			i++;
		}
	}
}

/*
** Function created to respect norminette rule
*/

static void		ft_norminette_rule(t_game *game, int i, float player_distance,
				t_img *img)
{
	float	wall_height;
	float	perp_distance;

	perp_distance = game->rays[i]->distance * cos(game->rays[i]->ray_angle -
					game->player->rotation_angle);
	wall_height = (TILE_SIZE / perp_distance) * player_distance;
	game->rays[i]->wall_top = (game->cubfile->height / 2)
								- (wall_height / 2);
	game->rays[i]->wall_top = (game->rays[i]->wall_top < 0) ? 0
								: game->rays[i]->wall_top;
	game->rays[i]->wall_bottom = (game->cubfile->height / 2)
									+ (wall_height / 2);
	game->rays[i]->wall_bottom = (game->rays[i]->wall_bottom
							> game->cubfile->height) ? game->cubfile->height
							: game->rays[i]->wall_bottom;
	ft_draw_ceiling(game, img, i);
	ft_draw_wall(game, img, wall_height, i);
	ft_draw_floor(game, img, i);
}

void			ft_draw_3d_map(t_game *game, t_img *img)
{
	float	player_distance;
	int		i;

	i = 0;
	player_distance = (game->cubfile->width / 2)
	/ tan(ft_degtorad(FOV_ANGLE / 2));
	while (i < (game->cubfile->width / WALL_STRIP_WIDTH))
	{
		ft_norminette_rule(game, i, player_distance, img);
		i++;
	}
}
