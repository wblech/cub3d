/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:05:35 by wbertoni          #+#    #+#             */
/*   Updated: 2020/12/26 13:52:21 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_x_to_check(float next_x, float ray_angle, int is_vert)
{
	return (next_x
		+ ((ft_calc_facing(ray_angle, left) && is_vert) ? -1 : 0));
}

float	get_y_to_check(float next_y, float ray_angle, int is_vert)
{
	return (next_y
		+ ((ft_calc_facing(ray_angle, up) && !is_vert) ? -1 : 0));
}

/*
** Function only to help fullfill the norminette rules
*/

void	ft_helper_rc(t_game *game, t_ray **rays)
{
	if (game->rays != NULL)
		ft_del_rays(game);
	game->rays = rays;
}
