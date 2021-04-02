/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:44:26 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 15:41:23 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_del_rays(t_game *game)
{
	int i;
	int num_ray;

	num_ray = game->cubfile->width / WALL_STRIP_WIDTH;
	i = 0;
	while (i < num_ray)
	{
		free(game->rays[i]);
		i++;
	}
	free(game->rays);
}

static void	ft_del_texture(void *mlx_ptr, t_tex *texture)
{
	mlx_destroy_image(mlx_ptr, texture->img->img);
	free(texture->img);
	free(texture);
}

void		ft_del_texture_orchestrator(t_game *game)
{
	ft_del_texture(game->mlx_ptr, game->tex_def);
	ft_del_texture(game->mlx_ptr, game->north);
	ft_del_texture(game->mlx_ptr, game->south);
	ft_del_texture(game->mlx_ptr, game->east);
	ft_del_texture(game->mlx_ptr, game->west);
	ft_del_texture(game->mlx_ptr, game->sprite_tex);
}

static void	ft_del_sprite(t_game *game)
{
	int i;

	i = 0;
	while (i < game->cubfile->map->num_sprite)
	{
		free(game->sprite[i]);
		i++;
	}
	free(game->sprite);
}

int			ft_close(t_game *game)
{
	if (!game->bmp)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->rays != NULL)
		ft_del_rays(game);
	if (game->sprite != NULL)
		ft_del_sprite(game);
	ft_del_file(game->cubfile);
	ft_del_texture_orchestrator(game);
	if (game->frame != NULL)
	{
		mlx_destroy_image(game->mlx_ptr, game->frame->img);
		free(game->frame);
	}
	free(game->player);
	free(game->mlx_ptr);
	free(game);
	exit(0);
	return (1);
}
