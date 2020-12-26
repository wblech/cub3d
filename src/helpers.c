/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:52:06 by wbertoni          #+#    #+#             */
/*   Updated: 2020/12/26 13:57:43 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_is_pointer_null(void *ptr)
{
	return (!ptr ? TRUE : FALSE);
}

int		ft_get_error(int (*func)(void *), void *a, char *msg)
{
	int is_true;

	is_true = func(a);
	if (is_true)
		ft_putstr(msg);
	return (is_true);
}

float	ft_distance_between_points(t_point start, t_point end)
{
	return (sqrt(((end.y - start.y) * (end.y - start.y))
	+ ((end.x - start.x) * (end.x - start.x))));
}

int		ft_calc_facing(float ray_angle, t_face face)
{
	float is_facing_up;
	float is_facing_down;
	float is_facing_right;
	float is_facing_left;

	is_facing_down = (ray_angle < WEST && ray_angle > EAST) ? 1 : 0;
	is_facing_up = !is_facing_down;
	is_facing_right = (ray_angle > NORTH || ray_angle < SOUTH) ? 1 : 0;
	is_facing_left = !is_facing_right;
	if (face == up)
		return (is_facing_up);
	if (face == down)
		return (is_facing_down);
	if (face == right)
		return (is_facing_right);
	if (face == left)
		return (is_facing_left);
	return (0);
}
