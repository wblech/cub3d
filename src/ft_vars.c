/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:07:34 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/03 15:48:41 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_create_vars(t_vars *vars, t_map *map, char *path)
{
	vars->win_width = TILE_SIZE * map->num_col;
	vars->win_height = TILE_SIZE * map->num_row;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height, "Map");
	vars->map = map;
	vars->img = ft_create_image(vars->mlx, vars->win_width, vars->win_height);
	vars->player = ft_create_player(vars, 'S', 5.0);
	vars->rays = NULL;
	vars->file = ft_read_cubfile(vars, path);
	vars->texture = ft_create_texture(vars->mlx, "./img/eagle.xpm");
	if (!vars->mlx || !vars->win || !vars->img || !vars->player)
		return (0);
	return (1);
}

void ft_del_rays(t_vars *vars)
{
	int i;
	int num_ray;

	num_ray = vars->win_width / WALL_STRIP_WIDTH;
	i = 0;
	while (i < num_ray)
	{
		free(vars->rays[i]);
		i++;
	}
	free(vars->rays);
}

void ft_del_vars(t_vars *vars)
{
	ft_free_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img->img);
	free(vars->img);
	free(vars->player);
	ft_del_rays(vars);
	mlx_destroy_image(vars->mlx, vars->texture->img->img);
	free(vars->texture);
}
