/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:58:43 by wbertoni          #+#    #+#             */
/*   Updated: 2021/01/04 16:43:24 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_end_window(t_game *game, float x, float y)
{
	if (x <= 0 || x >= game->cubfile->map->num_col * TILE_SIZE || y >= game->cubfile->map->num_row * TILE_SIZE || y <= 0)
	{
		return (1);
	}
	return (0);
}

int ft_has_wall(t_game *game, float x, float y, char id)
{
	int index_x;
	int index_y;

	if (is_end_window(game, x, y))
		return (1);
	index_x = floor(x / TILE_SIZE);
	index_y = floor(y / TILE_SIZE);
	return (game->cubfile->map->map[index_y][index_x] == id ? 1 : 0);
}
