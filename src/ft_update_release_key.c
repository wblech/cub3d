/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_release_key.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:39:43 by wbertoni          #+#    #+#             */
/*   Updated: 2021/03/28 17:58:26 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_update_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player->walk_direction = 1;
	else if (keycode == KEY_S)
		game->player->walk_direction = -1;
	else if (keycode == KEY_D)
		game->player->walk_direction = +1;
	else if (keycode == KEY_A)
		game->player->walk_direction = -1;
	else if (keycode == ARROW_LEFT)
		game->player->turn_direction = -1;
	else if (keycode == ARROW_RIGHT)
		game->player->turn_direction = 1;
	else if (keycode == KEY_ESC)
		ft_close(game);
	if (keycode == KEY_M)
	{
		ft_change_minimap_status();
	}
	return (new_position_player(keycode, game));
}

int	ft_update_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player->walk_direction = 0;
	if (keycode == KEY_S)
		game->player->walk_direction = 0;
	if (keycode == KEY_A)
		game->player->turn_direction = 0;
	if (keycode == KEY_D)
		game->player->turn_direction = 0;
	return (TRUE);
}
