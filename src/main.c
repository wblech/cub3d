#include "cubfile.h"
#include "cub3d.h"

int ft_render(t_game *game)
{

	t_img *new_img;

	new_img = ft_create_img(game);
	if (!new_img)
		return (0);
	if (!ft_raycast(game))
		return (0);
	ft_draw_3d_map(game, new_img);
	if (g_minimap)
		ft_draw_2d_map(game, new_img);
	// ft_cast_sprite(vars);
	// ft_draw_sprite(vars, new_img);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, new_img->img, 0, 0);
	ft_destroy_free_set_img(game, new_img);
	return (1);
}

// float	ft_normalize_angle(double angle)
// {
// 	angle = remainderf(angle, 2 * PI);
// 	if (angle < 0)
// 		angle += (2 * PI);
// 	return (angle);
// }

int ft_initialize_window(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->mlx_ptr = mlx_init();
	if (ft_get_error(&ft_is_pointer_null, game->mlx_ptr, "Error:\nInitialiasing\
mlx_init"))
		return (FALSE);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->cubfile->width, game->cubfile->height, "Map");
	if (ft_get_error(&ft_is_pointer_null, game->win_ptr, "Error:\nInitialiasing\
mlx_new_window"))
		return (FALSE);
	game->rays = NULL;
	return (TRUE);
}


int ft_setup(t_game *game, char *path)
{
	g_minimap = FALSE;
	game->cubfile = ft_cubfile(path);
	if (ft_get_error(&ft_is_pointer_null, game->cubfile, "Error:\nCouldn´t \
get cubfile info"))
		return (FALSE);
	if (!ft_initialize_window(game) || !ft_get_player_position(game))
		return (FALSE);
	if (!ft_get_all_textures(game))
		return (FALSE);
	game->frame = ft_create_img(game);
	ft_raycast(game);
	ft_draw_3d_map(game, game->frame);
	if (g_minimap)
		ft_draw_2d_map(game, game->frame);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr , game->frame->img, 0, 0);

	// if (!ft_raycast(game))
	// 	return (0);
	// // ft_cast_sprite(game);
	// ft_draw_2d_map(game, game->img);
	// ft_draw_sprite(game, game->img);
	// mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (TRUE);
}


int	main(int argc, char **argv)
{
	t_game *game;

	if (argc < 2)
	{
		ft_putstr("Error:\nSecond argument must be a path to the map");
		return (1);
	}
	game = (t_game *)malloc(sizeof(t_game));
	if (!ft_setup(game, argv[1]))
		exit(1);

	if (!mlx_hook(game->win_ptr, 2, 1L << 0, ft_update_press, game))
		exit(1);
	if (!mlx_hook(game->win_ptr, 3, 1L << 1, ft_update_release, game))
		exit(1);
	if (!mlx_expose_hook(game->win_ptr, ft_render, game))
		exit(1);
	mlx_hook(game->win_ptr, 17, 1L << 17, ft_close, game);
	mlx_loop(game->mlx_ptr); //tem que ficar na main
	return (0);
}
