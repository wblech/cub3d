/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:12:31 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/09 18:21:42 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_create_2d_map(t_data *img, t_map *map)
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
			start = ft_create_point(MINIMAP_SCALE_FACTOR * (i_col * TILE_SIZE),
									MINIMAP_SCALE_FACTOR * (i_row * TILE_SIZE), 0x00000000);
			size = ft_create_point(MINIMAP_SCALE_FACTOR * TILE_SIZE,
								   MINIMAP_SCALE_FACTOR * TILE_SIZE,
								   (map->map[i_row][i_col] == '1') ? 0x00000000 : 0x00ffffff);
			ft_rect_filled_borderless(img, start, size);
			i_col++;
		}
		i_col = 0;
		i_row++;
	}
}

void ft_free_map(char **map)
{
	int i_row;

	i_row = 0;
	while (map[i_row] != '\0')
	{
		free(map[i_row]);
		i_row++;
	}
	free(map);
}

int ft_has_wall(t_vars *vars, int x, int y)
{
	int index_x;
	int index_y;

	if (is_end_window(vars, x, y))
		return (1);
	index_x = floor(x / TILE_SIZE);
	index_y = floor(y / TILE_SIZE);
	return (vars->map->map[index_y][index_x] != '0' ? 1 : 0);
}

void ft_check_collision(t_vars *vars)
{
	float move_step;
	float new_x;
	float new_y;

	move_step = vars->player->walk_direction * vars->player->move_speed;
	new_x = vars->player->x + cos(vars->player->rotation_angle) * move_step;
	new_y = vars->player->y + sin(vars->player->rotation_angle) * move_step;
	if (!ft_has_wall(vars, new_x, new_y))
	{
		vars->player->x = new_x;
		vars->player->y = new_y;
	}
}

int is_end_window(t_vars *vars, float x, float y)
{
	if (x <= 0 || x >= vars->map->num_col * TILE_SIZE || y
	>= vars->map->num_row * TILE_SIZE || y <= 0)
	{
		return (1);
	}
	return (0);
}
