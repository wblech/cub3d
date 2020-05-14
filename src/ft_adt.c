/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 15:18:16 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 21:01:47 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point ft_create_point(int x, int y, int color)
{
	t_point point;

	// point = malloc(sizeof(t_point));
	point.x = x;
	point.y = y;
	point.color = color;
	return (point);
}

// t_point	del_point(t_point *point)
// {
// 	free(point);
// }
