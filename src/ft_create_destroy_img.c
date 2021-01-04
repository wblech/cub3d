/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_destroy_img.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:49:27 by wbertoni          #+#    #+#             */
/*   Updated: 2021/01/04 18:02:53 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_create_img(t_game *game)
{
	t_img *img;

	img = (t_img *)malloc(sizeof(t_img));
	img->img = mlx_new_image(game->mlx_ptr, game->cubfile->width,
							game->cubfile->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
									&img->line_length, &img->endian);
	return (img);
}

void	ft_destroy_free_set_img(t_game *game, t_img *new_img)
{
	mlx_destroy_image(game->mlx_ptr, game->frame->img);
	free(game->frame);
	game->frame = new_img;
}
