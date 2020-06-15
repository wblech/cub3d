/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:07:34 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/15 00:12:11 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_create_vars(t_vars *vars, t_map *map, char *path)
{
	(void)map;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (0);
	vars->file = ft_cubfile(vars, path);
	if (!vars->file)
		return (0);
	vars->map = vars->file->map;
	vars->map->num_row = vars->file->map->num_row;
	vars->map->num_col = vars->file->map->num_col;
	vars->win_width = vars->file->width;
	vars->win_height = vars->file->height;
	vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height, "Map");
	if (!vars->win)
		return (0);
	vars->img = ft_create_image(vars->mlx, vars->win_width, vars->win_height);
	vars->player = ft_create_player(vars, vars->map->initial_pl_cardinal, 5.0);
	vars->rays = NULL;
	vars->texture = ft_create_texture(vars->mlx, "./img/eagle.xpm");
	if (!vars->img || !vars->player)
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
	ft_free_map(vars->map->map);
	mlx_destroy_image(vars->mlx, vars->img->img);
	free(vars->img);
	free(vars->player);
	ft_del_rays(vars);
	mlx_destroy_image(vars->mlx, vars->texture->img->img);
	free(vars->texture);
}
