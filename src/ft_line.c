/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:48:10 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/22 11:27:20 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function was created to respect the norminette rules. Since it would get
** more than 5 arguments. The step argument was declared inside the t_point
** increment.color. Since this variable inside the struct has the type integer
*/

static void	ft_draw_line(t_img *img, t_point current, t_point increment,
t_point start)
{
	int i;
	int step;

	i = 0;
	step = increment.color;
	while (i++ <= step)
	{
		my_mlx_pixel_put(img, roundf(current.x), roundf(current.y),
		start.color);
		current.x += increment.x;
		current.y += increment.y;
	}
}

void		ft_line_dda(t_img *img, t_point start, t_point end)
{
	int		delta_x;
	int		delta_y;
	int		step;
	t_point	increment;
	t_point	current;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	step = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
	increment.color = step;
	increment.x = delta_x / (float)step;
	increment.y = delta_y / (float)step;
	current.x = start.x;
	current.y = start.y;
	ft_draw_line(img, current, increment, start);
}
