/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:40:19 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/15 00:33:36 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_count = 0;

t_map *ft_fake_map()
{
	t_map *map_clone;
	int i_row;
	int i_col;
	// int map[11][15] = {
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	char map[11][15] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};
	i_row = 0;
	i_col = 0;
	map_clone = malloc(sizeof(t_map));
	map_clone->num_col = 15;
	map_clone->num_row = 11;
	map_clone->map = malloc(map_clone->num_row * sizeof(char *));

	while (i_row < map_clone->num_row)
	{
		map_clone->map[i_row] = (char *)malloc(map_clone->num_col * sizeof(char));
		while (i_col < map_clone->num_col)
		{
			map_clone->map[i_row][i_col] = map[i_row][i_col];
			i_col++;
		}
		i_col = 0;
		i_row++;
	}
	return (map_clone);
}

int ft_setup(t_vars *vars, char *path)
{
	t_map *map;

	g_minimap = TRUE;
	map = ft_fake_map();
	if (!ft_create_vars(vars, map, path))
		return (0);
	if (!ft_raycast(vars))
		return (0);
	ft_draw_2d_map(vars, vars->img);
	ft_draw_3d_map(vars, vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (1);
}

int main(int argc, char **argv)
{
	t_vars vars;

	if (argc < 2)
	{
		printf("Error:\nSecond argument must be a path to the map");
		return (1);
	}
	if (!ft_setup(&vars, argv[1]))
		exit(1);
	if (!mlx_hook(vars.win, 2, 1L << 0, ft_update_press, &vars))
		exit(1);
	if (!mlx_hook(vars.win, 3, 1L << 1, ft_update_release, &vars))
		exit(1);
	if (!mlx_hook(vars.win, 17, 1L << 17, ft_close, &vars))
		exit(1);
	if (!mlx_expose_hook(vars.win, ft_render, &vars))
		exit(1);
	mlx_loop(vars.mlx);
	return (0);
}
