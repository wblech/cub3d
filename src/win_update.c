/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:02:51 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 20:35:38 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_render(t_vars *vars)
{
	t_data *new_img;
	t_point center;
	t_point end;

	new_img = ft_create_image(vars->mlx, 600, 480);
	if (!new_img)
		return (1);
	vars->player->rotation_angle += vars->player->turn_direction * vars->player->rotatio_speed;
	ft_check_collision(vars);
	center = ft_create_point(vars->player->x, vars->player->y, 0x00ff0000);
	end = ft_create_point(center.x + cos(vars->player->rotation_angle) * 30,
						  center.y + sin(vars->player->rotation_angle) * 30, 0x00ff0000);
	ft_create_map(new_img, vars->map);
	ft_circle_filled(new_img, center, vars->player->radius);
	// ft_line_dda(new_img, center, end);
	ft_raycast(vars, new_img);
	mlx_put_image_to_window(vars->mlx, vars->win, new_img->img, 0, 0);
	ft_destroy_free_set_img(vars, new_img);
	return (0);
}

int ft_close(t_vars *vars)
{
	ft_del_vars(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int ft_update_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->player->walk_direction = 1;
	if (keycode == KEY_S)
		vars->player->walk_direction = -1;
	if (keycode == KEY_A)
		vars->player->turn_direction = -1;
	if (keycode == KEY_D)
		vars->player->turn_direction = 1;
	if (keycode == KEY_ESC)
	{
		ft_close(vars);
	}
	return (ft_render(vars));
}
int ft_update_release(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->player->walk_direction = 0;
	if (keycode == KEY_S)
		vars->player->walk_direction = 0;
	if (keycode == KEY_A)
		vars->player->turn_direction = 0;
	if (keycode == KEY_D)
		vars->player->turn_direction = 0;
	return (ft_render(vars));
}
