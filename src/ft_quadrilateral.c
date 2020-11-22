/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quadrilateral.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:40:41 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/02 12:29:18 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Function : ft_rect
** -----------------
** Description : Draws a rectangle to the screen without background.
** A rectangle is a four sided shape with every angle at ninety degrees.
** The border color is the t_point start.color
**
** img : pointer of the image
** start : location of the upper-left corner
** size: set the width and the height
**
** Return: nothing
*/

// void ft_rect(t_img *img, t_point start, t_point size)
// {
// 	int y;
// 	int i;

// 	i = 0;
// 	y = start.y;
// 	while (i < size.y)
// 	{
// 		if (y == start.y)
// 		{
// 			ft_line_dda(img, start, ft_create_point(start.x + size.x, start.y, start.color));
// 		}
// 		else if (i == size.y - 1)
// 		{
// 			ft_line_dda(img, ft_create_point(start.x, y, start.color),
// 						ft_create_point(start.x + size.x, y, start.color));
// 		}
// 		else
// 		{
// 			my_mlx_pixel_put(img, start.x, y, start.color);
// 			my_mlx_pixel_put(img, start.x + size.x, y, start.color);
// 		}
// 		y++;
// 		i++;
// 	}
// }

// /*
// ** Function: ft_rect_filled
// ** -------------------
// ** Description : Draws a rectangle to the screen with a background.
// ** A rectangle is a four sided shape with every angle at ninety degrees.
// ** The border color is the t_point start.color. The background color is the
// ** t_point size.color.
// **
// ** img: pointer of the image
// ** start: location of the upper-left corner
// ** size: set the width and height
// **
// ** Return: nothing
// */

// void ft_rect_filled(t_img *img, t_point start, t_point size)
// {
// 	int i;
// 	int y;

// 	y = start.y;
// 	i = 0;
// 	while (i < size.y)
// 	{
// 		if (y == start.y || i == size.y - 1)
// 			ft_line_dda(img, ft_create_point(start.x, y, start.color),
// 						ft_create_point(start.x + size.x, y, start.color));
// 		else
// 		{
// 			ft_line_dda(img, ft_create_point(start.x + 1, y, size.color),
// 						ft_create_point(start.x + (size.x - 1), y, size.color));
// 			my_mlx_pixel_put(img, start.x, y, start.color);
// 			my_mlx_pixel_put(img, start.x + size.x, y, start.color);
// 		}
// 		y++;
// 		i++;
// 	}
// }

// Está com problema aqui. Pois ele tenta escrever o quadrado fora da memória no eixo y
void ft_rect_filled_borderless(t_img *img, t_point start, t_point size) //borderless
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
