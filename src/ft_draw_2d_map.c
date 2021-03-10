/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_2d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:36:28 by wbertoni          #+#    #+#             */
/*   Updated: 2021/03/09 22:17:13 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_create_2d_map(t_img *img, t_map *map)
{
	t_point		start;
	t_point		size;
	int			i_row;
	int			i_col;

	i_row = 0;
	i_col = 0;
	while (i_row < map->num_row)
	{
		while (i_col < map->num_col)
		{
			start = ft_create_point(
				MINIMAP_SCALE_FACTOR * i_col * TILE_SIZE,
				MINIMAP_SCALE_FACTOR * i_row * TILE_SIZE,
				0x00000000);
			size = ft_create_point(MINIMAP_SCALE_FACTOR * TILE_SIZE,
			MINIMAP_SCALE_FACTOR * TILE_SIZE, (map->map[i_row][i_col] == '1')
									? 0x00000000
									: 0x00ffffff);
			ft_rect_filled_borderless(img, start, size);
			i_col++;
		}
		i_col = 0;
		i_row++;
	}
}

/*
** Get player x and y and draw a circle
*/

static void		ft_render_player_2d(t_player *player, t_img *img)
{
	t_point central;

	central = ft_create_point(MINIMAP_SCALE_FACTOR * player->x,
							MINIMAP_SCALE_FACTOR * player->y,
							0x00ff0000);
	ft_circle_filled(img, central, player->radius);
}

int				ft_draw_2d_map(t_game *game, t_img *img)
{
	t_point		start;
	t_point		end;
	int			i;

	i = 0;
	start = ft_create_point(
		MINIMAP_SCALE_FACTOR * game->player->x,
		MINIMAP_SCALE_FACTOR * game->player->y,
		0x00ff0000);
	ft_create_2d_map(img, game->cubfile->map);
	ft_render_player_2d(game->player, img);
	while (i < (game->cubfile->width / WALL_STRIP_WIDTH))
	{
		end = ft_create_point(MINIMAP_SCALE_FACTOR * game->rays[i]->wall_hit_x,
							MINIMAP_SCALE_FACTOR * game->rays[i]->wall_hit_y,
							0x00ff0000);
		ft_line_dda(img, start, end);
		i++;
	}
	render_map_sprites(game, img);
	return (TRUE);
}
