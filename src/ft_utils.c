/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:42:59 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 20:31:02 by wbertoni         ###   ########.fr       */
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

long double ft_degtorad(long double degree)
{
	return (degree * (M_PI / 180));
}
