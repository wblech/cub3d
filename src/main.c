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
	if (game->cubfile->map->num_sprite > 0)
		ft_render_sprite_projection(game, new_img);
	if (g_minimap)
		ft_draw_2d_map(game, new_img);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, new_img->img, 0, 0);
	ft_destroy_free_set_img(game, new_img);
	return (1);
}



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
	if (game->cubfile->map->num_sprite > 0){
		ft_get_all_sprites_pos(game);
		ft_render_sprite_projection(game, game->frame);
	}
	if (g_minimap)
		ft_draw_2d_map(game, game->frame);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->frame->img, 0, 0);

	return (TRUE);
}

static int	ft_is_cub(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 4;
	if (ft_memcmp(&str[i], ".cub", 4))
		return (0);
	return (1);
}

int			check_args(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putstr("No argument");
		exit(0);
	}
	else if (argc > 3)
	{
		ft_putstr("Too many arguments");
		exit(0);
	}
	else if (!(ft_is_cub(argv[1])))
	{
		ft_putstr("First argument is not .cub");
		exit(0);
	}
	else if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
	{
		ft_putstr("Second argument is invalid. Try --save");
		exit(0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_game *game;

	check_args(argc, argv);


	// if (argc < 2)
	// {
	// 	ft_putstr("Error:\nSecond argument must be a path to the map or the\
	// 	command -save");
	// 	return (1);
	// }
	game = (t_game *)malloc(sizeof(t_game));
	if (!ft_setup(game, argv[1]))
		exit(1);
	if (ft_memcmp(argv[2], "--save", 6) != 0)
	{
		save_bmp_file(game);
		ft_close(game);
	}

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
