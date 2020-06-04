/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 15:18:16 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/01 16:39:21 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point ft_create_point(float x, float y, int color)
{
	t_point point;

	point.x = x;
	point.y = y;
	point.color = color;
	return (point);
}

