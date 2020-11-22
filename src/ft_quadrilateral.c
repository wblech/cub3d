/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quadrilateral.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:40:41 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/22 11:12:19 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rect_filled_borderless(t_img *img, t_point start, t_point size)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (j < size.y)
	{
		while (i < size.x)
		{
			my_mlx_pixel_put(img, start.x + i, start.y + j, size.color);
			i++;
		}
		i = 0;
		j++;
	}
}
