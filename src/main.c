#include "mlx.h"
#include "cubfile.h"
#include "cub3d.h"

typedef struct s_game
{
	void *mlx_ptr;
	void *win_ptr;
} t_game;

int ft_create_game(t_game *game, t_file cubfile)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, cubfile.width,
									cubfile.height, "Map");
	if (!game->mlx_ptr|| !game->win_ptr)
		return (0);
	return (1);
}



int ft_setup(t_game *game, t_file cubfile)
{
	// g_minimap = FALSE;
	if (!ft_create_game(game, cubfile))
		return (0);
	// if (!ft_raycast(game))
	// 	return (0);
	// // ft_cast_sprite(game);
	// ft_draw_2d_map(game, game->img);
	// ft_draw_3d_map(game, game->img);
	// ft_draw_sprite(game, game->img);
	// mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (1);
}


int	main(int argc, char **argv)
{
	t_file *cubfile;
	t_img img;
	t_game game;

	cubfile = ft_cubfile(argv[1]);
	if (argc < 2)
	{
		ft_putstr("Error:\nSecond argument must be a path to the map");
		return (1);
	}
	if (!ft_setup(&game, *cubfile))
		exit(1);

	img.img = mlx_new_image(game.mlx_ptr, (*cubfile).width, (*cubfile).height);
	img.addr = mlx_get_data_addr((&game)->win_ptr, &img.bits_per_pixel,
									&img.line_length, &img.endian);

	int i = 0;
	while(i < 100)
	{

		my_mlx_pixel_put(&img, 100 + i, 100, 0x00ff0000);
		my_mlx_pixel_put(&img, 100 + i, 101, 0x00ff0000);
		i++;
	}

	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr , img.img, 0, 0);

	mlx_loop(game.mlx_ptr); //tem que ficar na main

	// ft_del_file(cubfile);
	// mlx_destroy_window(mlx, window_ptr);


	return (0);
}
