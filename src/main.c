#include "mlx.h"
#include "cubfile.h"
#include "cub3d.h"

void ft_del_rays(t_game *game)
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

int ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->rays != NULL)
		ft_del_rays(game);
	ft_del_file(game->cubfile);
	mlx_destroy_image(game->mlx_ptr, game->frame->img);
	free(game->player);
	free(game);
	exit(0);
	return (1);
}

t_img *ft_create_img(t_game *game)
{
	t_img *img;

	img = (t_img *)malloc(sizeof(t_img));
	img->img = mlx_new_image(game->mlx_ptr, game->cubfile->width,
							game->cubfile->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
									&img->line_length, &img->endian);
	return (img);
}

void ft_destroy_free_set_img(t_game *game, t_img *new_img)
{
	mlx_destroy_image(game->mlx_ptr, game->frame->img);
	free(game->frame);
	game->frame = new_img;
}

int ft_render(t_game *game)
{

	t_img *new_img;
	// t_point center;

	new_img = ft_create_img(game);
	if (!new_img)
		return (0);
	ft_raycast(game);
	ft_draw_2d_map(game, new_img);
	// center = ft_create_point(vars->player->x, vars->player->y, 0x00ff0000);
	// if (!ft_raycast(vars))
	// 	return (0);
	// ft_draw_3d_map(vars, new_img);
	// ft_cast_sprite(vars);
	// ft_draw_sprite(vars, new_img);
	// if (g_minimap)
	// 	ft_draw_2d_map(vars, new_img);
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



int ft_update_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player->walk_direction = 1;
	else if (keycode == KEY_S)
		game->player->walk_direction = -1;
	else if (keycode == KEY_D)
		game->player->walk_direction = +1;
	else if (keycode == KEY_A)
		game->player->walk_direction = -1;
	else if (keycode == ARROW_LEFT)
		game->player->turn_direction = -1;
	else if (keycode == ARROW_RIGHT)
		game->player->turn_direction = 1;
	else if (keycode == KEY_ESC)
		ft_close(game);
	// if (keycode == KEY_M)
	// {
	// 	ft_change_minimap_status();
	// }
	// return (ft_render(vars));
	// return (TRUE);
	return (new_position_player(keycode, game));
}
// int ft_update_release(int keycode, t_vars *vars)
// {
// 	if (keycode == KEY_W)
// 		vars->player->walk_direction = 0;
// 	if (keycode == KEY_S)
// 		vars->player->walk_direction = 0;
// 	if (keycode == KEY_A)
// 		vars->player->turn_direction = 0;
// 	if (keycode == KEY_D)
// 		vars->player->turn_direction = 0;
// 	return (ft_render(vars));
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
	// g_minimap = FALSE;
	game->cubfile = ft_cubfile(path);
	if (ft_get_error(&ft_is_pointer_null, game->cubfile, "Error:\nCouldn´t \
get cubfile info"))
		return (FALSE);
	if (!ft_initialize_window(game))
		return (FALSE);
	if (!ft_get_player_position(game))
		return (FALSE);
	game->frame = ft_create_img(game);
	ft_raycast(game);
	ft_draw_2d_map(game, game->frame);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr , game->frame->img, 0, 0);

	// if (!ft_raycast(game))
	// 	return (0);
	// // ft_cast_sprite(game);
	// ft_draw_2d_map(game, game->img);
	// ft_draw_3d_map(game, game->img);
	// ft_draw_sprite(game, game->img);
	// mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (TRUE);
}


int	main(int argc, char **argv)
{
	// t_img img;
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
	// if (!mlx_hook(game->win_ptr, 3, 1L << 1, ft_update_release, game))
	// 	exit(1);

	// if (!mlx_hook(game->win_ptr, 2, 1L << 0, ft_update_press, game))
	// 	exit(1);

	mlx_hook(game->win_ptr, 17, 1L << 17, ft_close, game);

	mlx_loop(game->mlx_ptr); //tem que ficar na main

	// ft_del_file(cubfile);
	// mlx_destroy_window(mlx, window_ptr);


	return (0);
}
