/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:07:34 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 17:55:20 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_create_vars(t_vars *vars, t_map *map)
{
	vars->win_width = TILE_SIZE * map->num_col;
	vars->win_heigth = TILE_SIZE * map->num_row;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_heigth,
	"Map");
	vars->map = map;
	vars->img = ft_create_image(vars->mlx, vars->win_width, vars->win_heigth);
	vars->player = ft_create_player(vars, 'S', 3.0);
	vars->rays = NULL;
}

void ft_del_vars(t_vars *vars)
{
	ft_free_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img->img);
	free(vars->img);
	free(vars->player);
}
