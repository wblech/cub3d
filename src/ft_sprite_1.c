/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:45:22 by wbertoni          #+#    #+#             */
/*   Updated: 2021/03/28 15:29:13 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_get_sprite_pos(t_game *game, int x, int y, int count)
{
	game->sprite[count] = (t_sprite *)malloc(sizeof(t_sprite));
	game->sprite[count]->x = x * TILE_SIZE + TILE_SIZE / 2;
	game->sprite[count]->y = y * TILE_SIZE + TILE_SIZE / 2;
	game->sprite[count]->visible = 0;
}

void		ft_get_all_sprites_pos(t_game *game)
{
	int x;
	int y;
	int count;
	int num_sprites;

	num_sprites = game->cubfile->map->num_sprite;
	x = 0;
	y = 0;
	count = 0;
	game->sprite = (t_sprite **)malloc(num_sprites * sizeof(t_sprite *));
	while (y < game->cubfile->map->num_row)
	{
		while (x < game->cubfile->map->num_col)
		{
			if (game->cubfile->map->map[y][x] == '2')
			{
				ft_get_sprite_pos(game, x, y, count);
				count++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void		ft_render_map_sprites(t_game *game, t_img *img)
{
	int		i;
	t_point	start;
	t_point	size;

	i = 0;
	while (i < game->cubfile->map->num_sprite)
	{
		start.x = game->sprite[i]->x * MINIMAP_SCALE_FACTOR;
		start.y = game->sprite[i]->y * MINIMAP_SCALE_FACTOR;
		size.x = 2;
		size.y = 2;
		size.color = (game->sprite[i]->visible) ? 0x000000 : 0xFF4444;
		ft_rect_filled_borderless(img, start, size);
		i++;
	}
}

t_sprite	ft_set_visible_sprites(t_game *game, int i,
float angle_sprite_player)
{
	t_point start;
	t_point end;

	start.x = game->sprite[i]->x;
	start.y = game->sprite[i]->y;
	end.x = game->player->x;
	end.y = game->player->y;
	game->sprite[i]->visible = TRUE;
	game->sprite[i]->angle = angle_sprite_player;
	game->sprite[i]->distance = ft_distance_between_points(start, end);
	return (*game->sprite[i]);
}

float		ft_get_angle_sprite_player(t_game *game, int i)
{
	float angle_sprite_player;

	angle_sprite_player = ft_normalize_angle(game->player->rotation_angle)
	- atan2(game->sprite[i]->y - game->player->y,
	game->sprite[i]->x - game->player->x);
	if (angle_sprite_player > PI)
		angle_sprite_player -= TWO_PI;
	if (angle_sprite_player < -PI)
		angle_sprite_player += TWO_PI;
	angle_sprite_player = fabs(angle_sprite_player);
	return (angle_sprite_player);
}
