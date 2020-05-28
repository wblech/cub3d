/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:28:21 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/26 14:14:57 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Function: ft_line
** -----------------
** Description: Draw a line from one position to the other.
** The line can be from any direction. It uses the Bresenham Algorithm
**
** img: the image struct
** color: the color of the line
** x1: initial x position
** y1: initial y position
** x2: end x position
** y2: end y position
**
** Return: none
*/

void ft_line(t_data *img, t_point start, t_point end)
{

	float dx = fabsf(end.x - start.x), sx = start.x < end.x ? 1 : -1;
	float dy = fabsf(end.y - start.y), sy = start.y < end.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for (;;)
	{
		my_mlx_pixel_put(img, start.x, start.y, start.color);
		// setPixel(x0, y0);
		if (start.x == end.x && start.y == end.y)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			start.y += sy;
		}
	}
}

// void ft_line(t_data *img, t_point start, t_point end)
// {
// 	int m_new;
// 	int slope_error_new;
// 	int y;
// 	int x;
// 	int xend;

// 	m_new = 2 * abs(end.y - start.y);
// 	slope_error_new = m_new - abs(end.x - start.x); // p0 = 2Δy - Δx
// 	// if (start.x > end.x)
// 	// {
// 	// 	x = end.x;
// 	// 	y = end.y;
// 	// 	xend = start.x;
// 	// }
// 	// else
// 	// {
// 	// 	x = start.x;
// 	// 	y = start.y;
// 	// 	xend = end.x;
// 	// }
// 	x = start.x;
// 	y = start.y;
// 	xend = end.x;
// 	int k = x;
// 	while (k < xend)
// 	{
// 		my_mlx_pixel_put(img, x, y, get_color(ft_create_point(x, y, 0), start, \
// 		end));
// 		slope_error_new += m_new; //p(k+1) = p(k) + 2Δy
// 		if (slope_error_new >= 0)
// 		{
// 			(start.y < end.y) ? y++ : y--;
// 			// y++;
// 			slope_error_new -= 2 * abs(end.x - start.x);
// 		}
// 		(start.x < end.x) ? x++ : x--;
// 		k++;
// 	}
// }

/*
** Function: ft_line_dda
** ----------------
** Description: Draw a line using the Digital Differential Analyzer(DDA)
**
** img: the image struct
** color: the color of the line
** x1: initial x position
** y1: initial y position
** x2: end x position
** y2: end y position
**
** Return: none
*/

// void ft_line_dda(t_data *img, t_point start, t_point end)
// {
// 	int dx = end.x - start.x;
// 	int dy = end.y - start.y;
// 	int steps;
// 	int k;
// 	float xincrement;
// 	float yincrement;
// 	float x = start.x;
// 	float y = start.y;

// 	if (abs(dx) > abs(dy))
// 		steps = abs(dx);
// 	else
// 		steps = abs(dy);

// 	xincrement = abs(dx) / (float)steps;
// 	yincrement = abs(dy) / (float)steps;
// 	my_mlx_pixel_put(img, ROUND(x), ROUND(y), get_color(ft_create_point(ROUND(x), ROUND(y), 0), start, end));
// 	for (k = 0; k < steps; k++)
// 	{
// 		if (start.x <= end.x)
// 			x += xincrement;
// 		else
// 			x -= xincrement;
// 		if (start.y <= end.y)
// 			y += yincrement;
// 		else
// 			y -= yincrement;
// 		// my_mlx_pixel_put(img, ROUND(x), ROUND(y), start.color);
// 		my_mlx_pixel_put(img, ROUND(x), ROUND(y), get_color(ft_create_point(ROUND(x), ROUND(y), 0), start, end));
// 	}
// }
// void ft_line_dda(t_data *img, t_point start, t_point end)
// {
// 	int dx = end.x - start.x;
// 	int dy = end.y - start.y;
// 	int steps;
// 	int k;
// 	float xincrement;
// 	float yincrement;
// 	float x = start.x;
// 	float y = start.y;

// 	if (abs(dx) > abs(dy))
// 		steps = abs(dx);
// 	else
// 		steps = abs(dy);

// 	xincrement = abs(dx) / (float)steps;
// 	yincrement = abs(dy) / (float)steps;
// 	my_mlx_pixel_put(img, ROUND(x), ROUND(y), get_color(ft_create_point(ROUND(x), ROUND(y), 0), start, end));
// 	for (k = 0; k < steps; k++)
// 	{
// 		if (start.x <= end.x)
// 			x += xincrement;
// 		else
// 			x -= xincrement;
// 		if (start.y <= end.y)
// 			y += yincrement;
// 		else
// 			y -= yincrement;
// 		// my_mlx_pixel_put(img, ROUND(x), ROUND(y), start.color);
// 		my_mlx_pixel_put(img, ROUND(x), ROUND(y), get_color(ft_create_point(ROUND(x), ROUND(y), 0), start, end));
// 	}
// }

void ft_line_dda(t_data *img, t_point start, t_point end)
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
		my_mlx_pixel_put(img, ROUND(current.x), ROUND(current.y), start.color);
		current.x += x_increment;
		current.y += y_increment;
	}
}

/*
** Function: ft_hline
** ------------------
** Description: Draw a horizontal line from left to right with a specific size_t
**
** img: a t_data struct
** x: initial x position
** y: initial y position
** color: the value color
** size: the size of the line in pixels.
**
** Return: none
*/

	void
	ft_hline(t_data *img, t_point start, int size)
{
	int i;

	i = 0;
	while (i < size)
		my_mlx_pixel_put(img, (start.x + i++), start.y, start.color);
}
