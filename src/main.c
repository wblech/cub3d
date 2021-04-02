/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:29:49 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 15:27:08 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"
#include "cub3d.h"

int			ft_render(t_game *game)
{
	t_img *new_img;

	new_img = ft_create_img(game);
	if (!new_img)
		return (0);
	if (!ft_raycast(game))
		return (0);
	ft_draw_3d_map(game, new_img);
	if (game->cubfile->map->num_sprite > 0)
		ft_render_sprite_projection(game, new_img);
	if (g_minimap)
		ft_draw_2d_map(game, new_img);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, new_img->img, 0, 0);
	ft_destroy_free_set_img(game, new_img);
	return (1);
}

int			ft_initialize_window(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->mlx_ptr = mlx_init();
	if (ft_get_error(&ft_is_pointer_null, game->mlx_ptr, "Error:\nInitialiasing\
mlx_init"))
		return (FALSE);
	ft_check_resolution(game);
	game->rays = NULL;
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->sprite = NULL;
	game->frame = NULL;
	return (TRUE);
}

static	int	ft_start_game_or_draw_bmp(t_game *game, int argc)
{
	if (argc == 2)
	{
		game->bmp = FALSE;
		game->win_ptr = mlx_new_window(game->mlx_ptr, game->cubfile->width,
		game->cubfile->height, "CUB3D :: By Wincenty");
		if (ft_get_error(&ft_is_pointer_null, game->win_ptr,
		"Error:\nInitialiasing mlx_new_window"))
			return (FALSE);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->frame->img, 0, 0);
	}
	else
	{
		game->bmp = TRUE;
		save_bmp_file(game);
		ft_close(game);
	}
	return (TRUE);
}

int			ft_setup(t_game *game, char *path, int argc)
{
	g_minimap = FALSE;
	if (!ft_setup_norminette(game, path))
		return (FALSE);
	game->frame = ft_create_img(game);
	ft_create_ray_once(game);
	ft_raycast(game);
	ft_draw_3d_map(game, game->frame);
	if (game->cubfile->map->num_sprite > 0)
	{
		ft_get_all_sprites_pos(game);
		ft_render_sprite_projection(game, game->frame);
	}
	if (g_minimap)
		ft_draw_2d_map(game, game->frame);
	if (ft_start_game_or_draw_bmp(game, argc) != TRUE)
		return (FALSE);
	return (TRUE);
}

int			main(int argc, char **argv)
{
	t_game *game;

	check_args(argc, argv);
	game = (t_game *)malloc(sizeof(t_game));
	if (!ft_setup(game, argv[1], argc))
		exit(1);
	if (!mlx_hook(game->win_ptr, 2, 1L << 0, ft_update_press, game))
		exit(1);
	if (!mlx_hook(game->win_ptr, 3, 1L << 1, ft_update_release, game))
		exit(1);
	if (!mlx_expose_hook(game->win_ptr, ft_render, game))
		exit(1);
	mlx_hook(game->win_ptr, 17, 1L << 17, ft_close, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
