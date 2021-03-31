/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_all_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:01:52 by wbertoni          #+#    #+#             */
/*   Updated: 2021/03/31 19:10:54 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_texture_exists(char *path)
{
	int fopen;

	fopen = open(path, O_RDONLY);
	if (fopen < 0)
	{
		perror("Error\n");
		ft_putstr(path);
		return (FALSE);
	}
	close(fopen);
	return (TRUE);
}

int	ft_orchestrator_check_file(t_game *game)
{
	if (!ft_check_texture_exists("./img/eagle.xpm"))
		return (FALSE);
	if (!ft_check_texture_exists(game->cubfile->north))
		return (FALSE);
	if (!ft_check_texture_exists(game->cubfile->south))
		return (FALSE);
	if (!ft_check_texture_exists(game->cubfile->east))
		return (FALSE);
	if (!ft_check_texture_exists(game->cubfile->west))
		return (FALSE);
	if (!ft_check_texture_exists(game->cubfile->sprite))
		return (FALSE);
	return (TRUE);
}

int	ft_get_all_textures(t_game *game)
{
	if (!ft_orchestrator_check_file(game))
		return (FALSE);
	game->tex_def = ft_create_texture(game->mlx_ptr, "./img/eagle.xpm");
	game->north = ft_create_texture(game->mlx_ptr, game->cubfile->north);
	game->south = ft_create_texture(game->mlx_ptr, game->cubfile->south);
	game->east = ft_create_texture(game->mlx_ptr, game->cubfile->east);
	game->west = ft_create_texture(game->mlx_ptr, game->cubfile->west);
	game->sprite_tex = ft_create_texture(game->mlx_ptr, game->cubfile->sprite);
	if (!game->tex_def || !game->north || !game->south || !game->east
	|| !game->west || !game->sprite_tex)
	{
		ft_putstr("Something went wrong while parsing texture files");
		return (FALSE);
	}
	return (TRUE);
}
