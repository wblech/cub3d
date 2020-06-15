/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:42:59 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/10 12:20:22 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Function: my_mlx_pixel_put
** -----------
** Description: A faster solution for mlx_pixel_put, since it´s a
** slow function. This function was copied from this site
** https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#compilation-on-macos
*/

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float ft_degtorad(float degree)
{
	return (degree * (M_PI / 180));
}

float ft_normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

int ft_calc_facing(float ray_angle, t_face face)
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

float ft_distance_between_points(t_point start, t_point end)
{
	return (sqrt(((end.y - start.y) * (end.y - start.y))
	+ ((end.x - start.x) * (end.x - start.x))));
}
