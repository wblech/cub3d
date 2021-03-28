/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:41:23 by wbertoni          #+#    #+#             */
/*   Updated: 2021/03/28 18:26:32 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	ft_get_cardinal(int cardinal)
{
	if (cardinal == 'N')
		return (NORTH);
	else if (cardinal == 'S')
		return (SOUTH);
	else if (cardinal == 'E')
		return (EAST);
	else if (cardinal == 'W')
		return (WEST);
	else
	{
		ft_putstr("Error: Something went wrong at ft_get_cardinal");
		return (-1);
	}
}

static void		calculate_offset_player(int keycode, t_game *game)
{
	t_point		next_posit;
	t_point		offset;
	float		move_step;

	move_step = game->player->walk_direction * game->player->move_speed;
	offset.x = (keycode == KEY_W || keycode == KEY_S) ?
		cos(game->player->rotation_angle) * move_step :
		cos(game->player->rotation_angle + SOUTH) * move_step;
	offset.y = (keycode == KEY_W || keycode == KEY_S) ?
		sin(game->player->rotation_angle) * move_step :
		sin(game->player->rotation_angle + SOUTH) * move_step;
	next_posit.x = game->player->x + offset.x;
	next_posit.y = game->player->y + offset.y;
	if (!(ft_has_wall(game, next_posit.x, next_posit.y, '1'))
	&& !(ft_has_wall(game, next_posit.x, next_posit.y, '2')))
	{
		game->player->x = next_posit.x;
		game->player->y = next_posit.y;
	}
}

int				new_position_player(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S ||
		keycode == KEY_A || keycode == KEY_D)
		calculate_offset_player(keycode, game);
	else if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
	{
		game->player->rotation_angle +=
		game->player->turn_direction * game->player->rotation_speed;
	}
	return (ft_render(game));
}

int				ft_get_player_position(t_game *game)
{
	int cardi;

	cardi = game->cubfile->map->initial_pl_cardinal;
	game->player = (t_player *)malloc(sizeof(t_player));
	if (ft_get_error(&ft_is_pointer_null, game->player, "Error:\nInitialiasing\
player struct"))
		return (FALSE);
	game->player->x = game->cubfile->map->initial_pl_x;
	game->player->y = game->cubfile->map->initial_pl_y;
	game->player->width = 5;
	game->player->height = 5;
	game->player->turn_direction = 0;
	game->player->walk_direction = 0;
	game->player->rotation_angle = ft_normalize_angle(ft_get_cardinal(cardi));
	if (game->player->rotation_angle < 0)
		return (FALSE);
	game->player->move_speed = 5;
	game->player->rotation_speed = 45 * (PI / 180);
	game->player->radius = 3;
	return (TRUE);
}
