#include "mlx.h"
#include "cubfile.h"
#include "cub3d.h"

int ft_is_pointer_null(void *ptr)
{
	return (!ptr ? TRUE : FALSE);
}

int ft_get_error(int (*func)(void *), void *a, char *msg)
{
	int is_true;

	is_true = func(a);
	if (is_true)
		ft_putstr(msg);
	return (is_true);
}

int ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	ft_del_file(game->cubfile);
	mlx_destroy_image(game->mlx_ptr, game->frame->img);
	free(game->player);
	free(game);
	exit(0);
	return (1);
}

int is_end_window(t_game *game, float x, float y)
{
	if (x <= 0 || x >= game->cubfile->map->num_col * g_tile_size || y
	>= game->cubfile->map->num_row * g_tile_size || y <= 0)
	{
		return (1);
	}
	return (0);
}

int ft_has_wall(t_game *game, float x, float y, char id)
{
	int index_x;
	int index_y;

	if (is_end_window(game, x, y))
		return (1);
	index_x = floor(x / g_tile_size);
	index_y = floor(y / g_tile_size);
	return (game->cubfile->map->map[index_y][index_x] == id ? 1 : 0);
}

void ft_create_2d_map(t_img *img, t_map *map)
{
	t_point start;
	t_point size;
	int i_row;
	int i_col;

	i_row = 0; // y
	i_col = 0; // x
	while (i_row < map->num_row)
	{
		while (i_col < map->num_col)
		{
			start = ft_create_point((MINIMAP_SCALE_FACTOR * (i_col * g_tile_size)),
									(MINIMAP_SCALE_FACTOR * (i_row * g_tile_size)), 0x00000000);
			size = ft_create_point(MINIMAP_SCALE_FACTOR * g_tile_size, MINIMAP_SCALE_FACTOR * g_tile_size,
								   (map->map[i_row][i_col] == '1') ? 0x00000000 : 0x00ffffff);
			ft_rect_filled_borderless(img, start, size);
			i_col++;
		}
		i_col = 0;
		i_row++;
	}
}

/*
** Get player x and y and draw a circle
*/
void ft_render_player_2d(t_player *player, t_img *img)
{
	t_point central;
	central = ft_create_point(MINIMAP_SCALE_FACTOR * player->x,
							MINIMAP_SCALE_FACTOR * player->y,
							0x00ff0000);
	ft_circle_filled(img, central, player->radius);
}

int ft_draw_2d_map(t_game *game, t_img *img)
{
	t_point start;
	t_point end;

	start = ft_create_point(
		MINIMAP_SCALE_FACTOR * game->player->x,
		MINIMAP_SCALE_FACTOR * game->player->y,
		0x00ff0000);
	end = ft_create_point(
		MINIMAP_SCALE_FACTOR * (game->player->x
		+ cosf(game->player->rotation_angle) * 40),
		MINIMAP_SCALE_FACTOR * (game->player->y
		+ sinf(game->player->rotation_angle) * 40),
		0x00000000);
	ft_create_2d_map(img, game->cubfile->map);
	ft_render_player_2d(game->player, img);
	ft_line_dda(img, start, end);
	return (TRUE);
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

static void	calculate_offset_player(int keycode, t_game *game)
{
	t_point	next_posit;
	t_point	offset;
	float		move_step;

	move_step = game->player->walk_direction * game->player->move_speed;
	offset.x = (keycode == KEY_W || keycode == KEY_S) ?
		cos(game->player->rotation_angle) * move_step :
		cos(game->player->rotation_angle + SOUTH) * move_step;
	offset.y = (keycode == KEY_W || keycode == KEY_S) ?
		sin(game->player->rotation_angle) * move_step :
		sin(game->player->rotation_angle + SOUTH) * move_step;
	next_posit.x = game->player->x + offset.x;
	next_posit.y = game->player->y + offset.y;
	// game->player->x = next_posit.x;
	// game->player->y = next_posit.y;
	if (!(ft_has_wall(game, next_posit.x, next_posit.y, '1'))
	&& !(ft_has_wall(game, next_posit.x, next_posit.y, '2')))
	{
		game->player->x = next_posit.x;
		game->player->y = next_posit.y;
	}
}

// float	ft_normalize_angle(double angle)
// {
// 	angle = remainderf(angle, 2 * PI);
// 	if (angle < 0)
// 		angle += (2 * PI);
// 	return (angle);
// }

static int	new_position_player(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S ||
		keycode == KEY_A || keycode == KEY_D)
		calculate_offset_player(keycode, game);
	else if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
	{
		game->player->rotation_angle +=
		game->player->turn_direction * game->player->rotation_speed;
		// game->player->rotation_angle =
		// ft_normalize_angle(game->player->rotation_angle);
	}
	return (ft_render(game));
}

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
	return (TRUE);
}

float ft_get_cardinal(int cardinal)
{
	if (cardinal == 'N')
		return (NORTH);
	else if (cardinal == 'S')
		return (SOUTH);
	else if (cardinal == 'E')
		return (EAST);
	else if (cardinal == 'W')
		return (WEST);
	else
	{
		ft_putstr("Error: Something went wrong at ft_get_cardinal");
		return (-1);
	}
}

int ft_get_player_position(t_game *game)
{
	int cardinal;

	cardinal = game->cubfile->map->initial_pl_cardinal;
	game->player = (t_player *)malloc(sizeof(t_player));
	if (ft_get_error(&ft_is_pointer_null, game->player, "Error:\nInitialiasing\
player struct"))
		return (FALSE);
	game->player->x = game->cubfile->map->initial_pl_x;
	game->player->y = game->cubfile->map->initial_pl_y;
	game->player->width = 5;
	game->player->height = 5;
	game->player->turn_direction = 0;
	game->player->walk_direction = 0;
	game->player->rotation_angle = ft_get_cardinal(cardinal);
	if (game->player->rotation_angle < 0)
		return (FALSE);
	game->player->move_speed = 5;
	game->player->rotation_speed = 45 * (PI / 180);
	game->player->radius = 3;
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

	game = (t_game *)malloc(sizeof(t_game));
	if (argc < 2)
	{
		ft_putstr("Error:\nSecond argument must be a path to the map");
		return (1);
	}
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
