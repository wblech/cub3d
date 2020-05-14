/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:12:31 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 20:36:27 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_create_map(t_data *img, t_map *map)
{
	t_point start;
	t_point size;
	int i_row;
	int i_col;

	i_row = 0;
	i_col = 0;
	while (i_row < map->num_row)
	{
		while (i_col < map->num_col)
		{
			start = ft_create_point(i_col * TILE_SIZE, i_row * TILE_SIZE,
									0x00000000);
			size = ft_create_point(TILE_SIZE, TILE_SIZE,
								   (map->map[i_row][i_col]) ? 0x00000000 : 0x00ffffff);
			ft_rect_filled(img, start, size);
			i_col++;
		}
		i_col = 0;
		i_row++;
	}
}

void ft_free_map(t_map *map)
{
	int i_row;

	i_row = 0;
	while (i_row < map->num_row)
	{
		free(map->map[i_row]);
		i_row++;
	}
	free(map);
}

int ft_has_wall(t_map *map, int x, int y)
{
	int index_x;
	int index_y;

	index_x = floor(x / TILE_SIZE);
	index_y = floor(y / TILE_SIZE);
	return (map->map[index_y][index_x] != 0 ? 1 : 0);
}

void ft_check_collision(t_vars *vars)
{
	long double move_step;
	int new_x;
	int new_y;

	move_step = vars->player->walk_direction * vars->player->move_speed;
	new_x = vars->player->x + cos(vars->player->rotation_angle) * move_step;
	new_y = vars->player->y + sin(vars->player->rotation_angle) * move_step;
	if (!ft_has_wall(vars->map, new_x, new_y))
	{
		vars->player->x = new_x;
		vars->player->y = new_y;
	}
}
