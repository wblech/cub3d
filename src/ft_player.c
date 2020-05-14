/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 09:30:47 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 20:31:02 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player *ft_create_player(t_vars *vars, char cardinal, long double speed)
{
	t_player *pl;

	pl = malloc(sizeof(t_player));
	pl->x = vars->win_width / 2;
	pl->y = vars->win_heigth / 2;
	pl->radius = 3;
	if (cardinal == 'N')
		pl->rotation_angle = NORTH;
	else if (cardinal == 'S')
		pl->rotation_angle = SOUTH;
	else if (cardinal == 'E')
		pl->rotation_angle = EAST;
	else if (cardinal == 'W')
		pl->rotation_angle = WEST;
	else
		return (NULL);
	pl->turn_direction = 0;
	pl->walk_direction = 0;
	pl->move_speed = speed;
	pl->rotatio_speed = ft_degtorad(speed);
	return (pl);
}

// int		ft_draw_player(t_player *player)
// {

// }

// void	ft_move(int keycode, t_vars vars)
// {
// 	mlx_loop_hook(vars.mlx, )
// }
