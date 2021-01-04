/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_all_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:01:52 by wbertoni          #+#    #+#             */
/*   Updated: 2021/01/04 18:22:54 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_all_textures(t_game *game)
{
	game->tex_def = ft_create_texture(game->mlx_ptr, "./img/eagle.xpm");
	game->north = ft_create_texture(game->mlx_ptr, game->cubfile->north);
	game->south = ft_create_texture(game->mlx_ptr, game->cubfile->south);
	game->east = ft_create_texture(game->mlx_ptr, game->cubfile->east);
	game->west = ft_create_texture(game->mlx_ptr, game->cubfile->west);
	if (!game->tex_def || !game->north || !game->south || !game->east
	|| !game->west)
	{
		ft_putstr("Something went wrong while parsing texture files");
		return (FALSE);
	}
	return (TRUE);
}
