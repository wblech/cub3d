/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:58:43 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/22 11:09:38 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_end_window(t_game *game, float x, float y)
{
	if (x <= 0 || x >= game->cubfile->map->num_col * g_tile_size || y
	>= game->cubfile->map->num_row * g_tile_size || y <= 0)
	{
		return (1);
	}
	return (0);
}

int	ft_has_wall(t_game *game, float x, float y, char id)
{
	int index_x;
	int index_y;

	if (is_end_window(game, x, y))
		return (1);
	index_x = floor(x / g_tile_size);
	index_y = floor(y / g_tile_size);
	return (game->cubfile->map->map[index_y][index_x] == id ? 1 : 0);
}
