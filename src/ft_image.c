/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:10:51 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/13 12:11:11 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data *ft_create_image(void *mlx_ptr, int x, int y)
{
	t_data *img;

	img = malloc(1 * sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx_ptr, x, y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
								  &img->line_length, &img->endian);
	return (img);
}

void ft_destroy_free_set_img(t_vars *vars, t_data *new_img)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	free(vars->img);
	vars->img = new_img;
}
