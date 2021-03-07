#include "cubfile.h"
#include "cub3d.h"

//sprite

#define NUM_SPRITES 1

static t_sprite sprites[NUM_SPRITES] = {
	{ .x = 1500, .y = 440}
};

//void

void render_map_sprites(t_img *img){ //minimap
	int i;
	t_point start;
	t_point size;

	i = 0;
	while (i < NUM_SPRITES) {
		start.x = sprites[i].x * MINIMAP_SCALE_FACTOR;
		start.y = sprites[i].y * MINIMAP_SCALE_FACTOR;
		size.x = 2;
		size.y = 2;
		size.color = (sprites[i].visible) ? 0x000000 : 0xFF4444;
		ft_rect_filled_borderless(img, start, size);
		i++;
	}
}

void render_sprite_projection(t_game *game, t_img *img){
	t_sprite visible_sprites[NUM_SPRITES];
	int num_visible_sprites = 0;
	int i;
	float angle_sprite_player;

	i = 0;
	//Find sprites that are visible (inside the FOV)
	while ( i < NUM_SPRITES) {
		angle_sprite_player = ft_normalize_angle(game->player->rotation_angle)
		- atan2(sprites[i].y - game->player->y, sprites[i].x - game->player->x);

		//make sure the angle is always between 0 and 180 degree - Create func
		if (angle_sprite_player > PI)
			angle_sprite_player -= TWO_PI;
		if (angle_sprite_player < -PI)
			angle_sprite_player += TWO_PI;
		angle_sprite_player = fabs(angle_sprite_player);
		// end func
		if (angle_sprite_player < (ft_degtorad(FOV_ANGLE) / 2)) {
			// create func

			t_point start;
			t_point end;

			start.x = sprites[i].x;
			start.y = sprites[i].y;
			end.x = game->player->x;
			end.y = game->player->y;

			sprites[i].visible = TRUE;
			sprites[i].angle = angle_sprite_player;
			sprites[i].distance = ft_distance_between_points(start, end);
			visible_sprites[num_visible_sprites] = sprites[i];
			//end func
			num_visible_sprites++;
		}
		else {
			sprites[i].visible = FALSE;
		}
		i++;
	}

	// Rendering all the visible sprites - Create function
	int w;

	w = 0;
	while (w < num_visible_sprites) {
		t_sprite sprite = visible_sprites[w];
		float player_distance;

		//Calculate the sprite projected height
		float sprite_height;
		float sprite_width;
		//((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))
		player_distance = (game->cubfile->width / 2)
	/ tan(ft_degtorad(FOV_ANGLE) / 2 );
		sprite_height = (TILE_SIZE / sprite.distance) * player_distance;
		sprite_width = sprite_height;

		// Sprite top Y
		float sprite_top_y;
		float sprite_bottom_y;

		sprite_top_y = (game->cubfile->height / 2) - (sprite_height / 2);
		sprite_top_y = (sprite_top_y < 0) ? 0 : sprite_top_y;

		// Sprite botton Y
		sprite_bottom_y = (game->cubfile->height / 2) + (sprite_height / 2);
		sprite_bottom_y = (sprite_bottom_y > game->cubfile->height)
		? game->cubfile->height : sprite_bottom_y;

		// Calculate the sprite X position in the projection plane
		float sprite_angle;
		float sprite_screen_posx;

		sprite_angle = atan2(sprite.y - game->player->y, sprite.x
		- game->player->x) - game->player->rotation_angle;
		sprite_screen_posx = tan(sprite_angle) * player_distance;

		// SpriteLeftX
		float sprite_left_x;

		sprite_left_x = (game->cubfile->width / 2) + sprite_screen_posx;

		// SpriteRightX
		float sprite_right_x;

		sprite_right_x = sprite_left_x + sprite_width;

		// Loop alll the x values
		int x;
		int y;

		x = sprite_left_x;
		y = sprite_top_y;
		while (x < sprite_right_x) {
			while (y < sprite_bottom_y) {
				if (x > 0 && x < game->cubfile->width
				&& y > 0 && y < game->cubfile->height)
					my_mlx_pixel_put(img, x, y, 0xFFFF0000);
				y++;
			}
			y = sprite_top_y;
			x++;
		}
		w++;
	}

	// end func

}
//end sprite

int ft_render(t_game *game)
{

	t_img *new_img;

	new_img = ft_create_img(game);
	if (!new_img)
		return (0);
	if (!ft_raycast(game))
		return (0);
	ft_draw_3d_map(game, new_img);
	render_sprite_projection(game, new_img);
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
	render_sprite_projection(game, game->frame);
	if (g_minimap)
		ft_draw_2d_map(game, game->frame);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->frame->img, 0, 0);

	return (TRUE);
}

int main(int argc, char **argv)
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
