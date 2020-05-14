/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:00:17 by wbertoni          #+#    #+#             */
/*   Updated: 2020/04/28 17:42:02 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Function: add_shades
** ----------
** Description: Add shade to the ARGB color. It does not affect the transparency.
**
** dst: the percentage of the shade. 0 will add no shading. 1 will make the color
** completely dark. 0.5 will dim it halfway, and 0.25 a quarter and so on
** color: the ARGB color to be shaded
**
** Return: an integer with the value of the color shaded
*/

int	add_shades(double dst, int color)
{
	int t;
	int r;
	int g;
	int b;

	if (dst >= 1)
		return (0);
	if (dst <= 0)
		return (color);

	r = ((color >> 16) & 0xFF) * dst;
	g = ((color >> 8) & 0xFF) * dst;
	b = ((color) & 0xFF) * dst;
	t = ((color >> 24) & 0xFF);
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** Function: get_opposite
** ---------
** Description : is a function that accepts an int(color) as argument and that
** will invert the color accordingly
**
** color: the ARGB color to be inverted
**
** Return: an int ARGB color with the opposit bits from the color in the
** parameter
*/

int get_opposite(int color)
{
	int t;
	int r;
	int g;
	int b;

	r = ~(color >> 16);
	g = ~(color >> 8);
	b = ~(color);
	t = (color >> 24) & 0xFF;
	return (t << 24 | r << 16 | g << 8 | b);
}

static double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static int get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_point current, t_point start, t_point end)
{
	int		t;
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if ((end.x - start.x) > (end.y - start.y))
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, \
	percentage);
	green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, \
	percentage);
	blue = get_light((start.color) & 0xFF, (end. color) & 0xFF, percentage);
	t = (start.color >> 24) & 0xFF;
	return(t << 24 | red << 16 | green << 8 | blue);
}
