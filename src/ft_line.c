/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:48:10 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/02 13:51:52 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_line_dda(t_img *img, t_point start, t_point end)
{
	int delta_x;
	int delta_y;
	int step;
	float x_increment;
	float y_increment;
	t_point current;
	int i;

	i = 0;
	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	step = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
 	x_increment = delta_x / (float)step;
 	y_increment = delta_y / (float)step;
	current.x = start.x;
	current.y = start.y;
	while (i++ <= step)
	{
		my_mlx_pixel_put(img, roundf(current.x), roundf(current.y), start.color);
		current.x += x_increment;
		current.y += y_increment;
	}
}
