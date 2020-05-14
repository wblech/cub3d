/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:31:13 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 20:31:02 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Function: ft_circle_polar
** ---------------
** Description: Draw a circle using the polar positions (cos, sen and theta)
**
** img: the pointer to the struct t_data
** x: the x position of the circle´s center
** x: th y position of the circle´s center
** r: the circles radians
** color: the value of the color
**
** Return: nothing
**
*/

void ft_circle_polar(t_data *img, t_point pos, int radians)
{
	long double angle;
	long double increase_angle = 0.01;
	int new_x;
	int new_y;

	angle = 0.0;
	while (angle < 2 * M_PI)
	{
		new_x = pos.x + (radians * cos(angle));
		new_y = pos.y + (radians * sin(angle));
		my_mlx_pixel_put(img, new_x, new_y, pos.color);
		angle += increase_angle;
	}
}

static void sym_circle(t_data *img, t_point center, int x, int y)
{
	my_mlx_pixel_put(img, (center.x + x), (center.y + y), center.color);
	my_mlx_pixel_put(img, (center.x - x), (center.y + y), center.color);
	my_mlx_pixel_put(img, (center.x + x), (center.y - y), center.color);
	my_mlx_pixel_put(img, (center.x - x), (center.y - y), center.color);
	my_mlx_pixel_put(img, (center.x + y), (center.y + x), center.color);
	my_mlx_pixel_put(img, (center.x - y), (center.y + x), center.color);
	my_mlx_pixel_put(img, (center.x + y), (center.y - x), center.color);
	my_mlx_pixel_put(img, (center.x - y), (center.y - x), center.color);
}

/*
** Function: ft_circle
** ---------------
** Description: Draw a circle using the Midpoint Circle Algorithm
**
** img: the pointer to the struct t_data
** xc: the x position of the circle´s center
** xy: th y position of the circle´s center
** r: the circles radians
** color: the value of the color
**
** Return: nothing
**
*/

void ft_circle(t_data *img, t_point center, int r)
{
	int x;
	int y;
	int pk;

	x = 0;
	y = r;
	pk = 1 - r;
	sym_circle(img, center, x, y);
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
		sym_circle(img, center, x, y);
	}
}

static void sym_circle_filled(t_data *img, t_point center, int x, int y)
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

void ft_circle_filled(t_data *img, t_point center, int r)
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
