/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:45:22 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 09:47:59 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_get_visible_sprites(t_game *game, t_sprite *visible_sprites)
{
	int		nbr_vis_sp;
	int		i;
	float	angle_sprite_player;
	float	epsilon;

	angle_sprite_player = 0.0;
	nbr_vis_sp = 0;
	epsilon = 0.2;
	i = 0;
	while (i < game->cubfile->map->num_sprite)
	{
		angle_sprite_player = ft_get_angle_sprite_player(game, i);
		if (angle_sprite_player < (ft_degtorad(FOV_ANGLE) / 2) + epsilon)
		{
			visible_sprites[nbr_vis_sp] =
			ft_set_visible_sprites(game, i, angle_sprite_player);
			nbr_vis_sp++;
		}
		else
		{
			game->sprite[i]->visible = FALSE;
		}
		i++;
	}
	return (nbr_vis_sp);
}

static void	ft_plot_pixel(t_game *game, t_img *img, t_sprite sprite,
t_point pos)
{
	float	texel_width;
	int		color;
	int		distance_from_top;
	t_point	texture;

	texel_width = (game->sprite_tex->width / sprite.width);
	texture.x = (pos.x - sprite.left_x) * texel_width;
	color = 0;
	while (pos.y < sprite.bottom_y)
	{
		if (pos.x > 0 && pos.x < game->cubfile->width
		&& pos.y > 0 && pos.y < game->cubfile->height)
		{
			distance_from_top = pos.y + (sprite.height / 2)
			- (game->cubfile->height / 2);
			texture.y = distance_from_top
			* (game->sprite_tex->height / sprite.height);
			color = ft_texture_byte(game->sprite_tex, texture);
			if (sprite.distance < game->rays[(int)pos.x]->distance
			&& color != (int)0xff000000 && color)
				my_mlx_pixel_put(img, pos.x, pos.y, color);
		}
		pos.y++;
	}
}

static void	ft_calc_plot_pixel(t_game *game, t_img *img, t_sprite sprite)
{
	t_point x_y;

	x_y.x = sprite.left_x;
	x_y.y = sprite.top_y;
	while (x_y.x < sprite.right_x)
	{
		ft_plot_pixel(game, img, sprite, x_y);
		x_y.x++;
	}
}

void		ft_draw_sprite_3d(t_game *game, t_img *img, t_sprite sprite)
{
	float player_distance;

	player_distance = (game->cubfile->width / 2)
	/ tan(ft_degtorad(FOV_ANGLE) / 2);
	sprite.height = (TILE_SIZE / sprite.distance) * player_distance;
	sprite.width = sprite.height;
	sprite.top_y = (game->cubfile->height / 2) - (sprite.height / 2);
	sprite.top_y = (sprite.top_y < 0) ? 0 : sprite.top_y;
	sprite.bottom_y = (game->cubfile->height / 2) + (sprite.height / 2);
	sprite.bottom_y = (sprite.bottom_y > game->cubfile->height)
	? game->cubfile->height : sprite.bottom_y;
	sprite.angle_3d = atan2(sprite.y - game->player->y, sprite.x
	- game->player->x) - ft_normalize_angle(game->player->rotation_angle);
	sprite.screen_posx = tan(sprite.angle_3d) * player_distance;
	sprite.left_x = (game->cubfile->width / 2) + sprite.screen_posx
	- (sprite.width / 2);
	sprite.right_x = sprite.left_x + sprite.width;
	ft_calc_plot_pixel(game, img, sprite);
}

void		ft_render_sprite_projection(t_game *game, t_img *img)
{
	t_sprite	visible_sprites[game->cubfile->map->num_sprite];
	int			num_visible_sprites;
	int			i;
	int			w;

	i = 0;
	num_visible_sprites = ft_get_visible_sprites(game, &visible_sprites[0]);
	ft_sort_sprites(num_visible_sprites, &visible_sprites[0]);
	w = 0;
	while (w < num_visible_sprites)
	{
		ft_draw_sprite_3d(game, img, visible_sprites[w]);
		w++;
	}
}
