/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_player_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 08:43:49 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 08:53:37 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

void	ft_set_player_position(t_file *file, int i, int j)
{
	file->map->initial_pl_cardinal = file->map->map[i][j];
	file->map->initial_pl_x = j * TILE_SIZE;
	file->map->initial_pl_y = i * TILE_SIZE;
	file->map->map[i][j] = '0';
}
