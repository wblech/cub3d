/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:53:20 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/01 18:58:24 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_resolution(t_game *game)
{
	int screen_width;
	int screen_height;

	mlx_get_screen_size(game->mlx_ptr, &screen_width, &screen_height);
	if (game->cubfile->width > screen_width)
		game->cubfile->width = screen_width;
	if (game->cubfile->height > screen_height)
		game->cubfile->height = screen_height;
}
