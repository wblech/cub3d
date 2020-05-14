/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:40:19 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 20:57:31 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map *ft_fake_map()
{
	t_map *map_clone;
	int i_row;
	int i_col;
	int map[11][15] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	i_row = 0;
	i_col = 0;
	map_clone = malloc(sizeof(t_map));
	map_clone->num_col = 15;
	map_clone->num_row = 11;
	map_clone->map = malloc(map_clone->num_row * sizeof(int *));

	while (i_row < map_clone->num_row)
	{
		map_clone->map[i_row] = (int *)malloc(map_clone->num_col * sizeof(int));
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

// t_ray	*ft_create_ray(t_vars *vars)
// {
// 	t_ray *ray;

// 	ray = malloc(sizeof(t_ray));
// 	ray->fov_angle = ft_degtorad(FOV_ANGLE);
// 	ray->num_ray = vars->win_width / WALL_STRIP_WIDTH;
// 	return (ray);
// }

// void	del_ray(t_ray *rey)
// {
// 	free(rey);
// }

void ft_create_rays(t_vars *vars)
{
	long double fov_angle;
	long double ray_angle;
	long double num_ray;
	t_point *rays;
	int i;

	i = 0;
	fov_angle = ft_degtorad(FOV_ANGLE);
	num_ray = vars->win_width / WALL_STRIP_WIDTH;
	ray_angle = vars->player->rotation_angle - (fov_angle / 2);
	rays = malloc(num_ray * sizeof(t_point));
	while (i < num_ray)
	{
		rays[i] = ft_create_point(vars->player->x + cos(ray_angle) * 100,
								  vars->player->y + sin(ray_angle) * 100, 0x00ff0000);
		ray_angle += fov_angle / num_ray;
		i++;
	}
	if (vars->rays != NULL)
		free(vars->rays);
	vars->rays = rays;
}

void ft_raycast_render(t_vars *vars, t_data *img)
{
	int i;
	t_point central;

	i = 0;
	central = ft_create_point(vars->player->x, vars->player->y, 0x00ff0000);
	while (i < (vars->win_width / WALL_STRIP_WIDTH))
	{
		ft_line_dda(img, central, vars->rays[i]);
		i++;
	}
}

void ft_raycast(t_vars *vars, t_data *img)
{
	ft_create_rays(vars);
	ft_raycast_render(vars, img);
}

void ft_setup(t_vars *vars)
{
	t_map *map;
	t_point central;
	t_point end;

	map = ft_fake_map();
	ft_create_vars(vars, map);
	central = ft_create_point(vars->player->x, vars->player->y, 0x00ff0000);
	end = ft_create_point(central.x + cos(vars->player->rotation_angle) * 30,
						  central.y + sin(vars->player->rotation_angle) * 30, central.color);
	ft_create_map(vars->img, vars->map);
	ft_circle_filled(vars->img, central, vars->player->radius);
	ft_raycast(vars, vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

int main(void)
{
	t_vars vars;
	t_map *map;

	map = ft_fake_map();
	ft_setup(&vars);
	mlx_hook(vars.win, 2, 1L << 0, ft_update_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, ft_update_release, &vars);
	mlx_hook(vars.win, 17, 1L << 17, ft_close, &vars);
	mlx_expose_hook(vars.win, ft_render, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
