/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:43:41 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/02 13:44:14 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void sym_circle_filled(t_img *img, t_point center, int x, int y)
{
	t_point start[4];
	t_point end[4];
	int i;

	start[0] = ft_create_point((center.x - x), (center.y + y), center.color);
	end[0] = ft_create_point((center.x + x), (center.y + y), center.color);
	start[1] = ft_create_point((center.x - x), (center.y - y), center.color);
	end[1] = ft_create_point((center.x + x), (center.y - y), center.color);
	start[2] = ft_create_point((center.x - y), (center.y + x), center.color);
	end[2] = ft_create_point((center.x + y), (center.y + x), center.color);
	start[3] = ft_create_point((center.x - y), (center.y - x), center.color);
	end[3] = ft_create_point((center.x + y), (center.y - x), center.color);
	i = 0;
	while (i <= 3)
	{
		ft_line_dda(img, start[i], end[i]);
		i++;
	}
}

void ft_circle_filled(t_img *img, t_point center, int r)
{
	int x;
	int y;
	int pk;

	x = 0;
	y = r;
	pk = 1 - r;
	sym_circle_filled(img, center, x, y);
	while (x <= y)
	{
		x++;
		if (pk < 0)
		{
			pk += 2 * x + 1;
		}
		else
		{
			y--;
			pk += 2 * (x - y) + 1;
		}
		sym_circle_filled(img, center, x, y);
	}
}
