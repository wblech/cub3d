/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 09:30:47 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/01 16:41:23 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player *ft_create_player(t_vars *vars, char cardinal, float speed)
{
	t_player *pl;

	pl = (t_player *)malloc(sizeof(t_player));
	if (!pl)
		return (NULL);
	pl->x = vars->win_width / 2;
	pl->y = vars->win_height / 2;
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
