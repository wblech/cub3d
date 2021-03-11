#include "cubfile.h"
#include "cub3d.h"

//sprite

// #define NUM_SPRITES 3

// static t_sprite sprites[NUM_SPRITES] = {
// 	{ .x = 1500, .y = 440},
// 	{ .x = 1400, .y = 440},
// 	{ .x = 1300, .y = 440}
// };

//Precisa fazer o free destes mallocs
void ft_get_sprite_pos(t_game *game, int x, int y, int count){
	game->sprite[count] = (t_sprite *)malloc(sizeof(t_sprite));
	game->sprite[count]->x = x * TILE_SIZE;
	game->sprite[count]->y = y * TILE_SIZE;
	game->sprite[count]->visible = 0;
}

void ft_get_all_sprites_pos(t_game *game) {
	int x;
	int y;
	int count;
	int num_sprites;

	num_sprites = game->cubfile->map->num_sprite;
	x = 0;
	y = 0;
	count = 0;
	game->sprite = (t_sprite **)malloc(num_sprites * sizeof(t_sprite *));
	while (y < game->cubfile->map->num_row){
		while(x < game->cubfile->map->num_col) {
			if (game->cubfile->map->map[y][x] == '2') {
				ft_get_sprite_pos(game, x, y, count);
				count++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

//void

void render_map_sprites(t_game *game, t_img *img){ //minimap
	int i;
	t_point start;
	t_point size;

	i = 0;
	while (i < game->cubfile->map->num_sprite) {
		start.x = game->sprite[i]->x * MINIMAP_SCALE_FACTOR;
		start.y = game->sprite[i]->y * MINIMAP_SCALE_FACTOR;
		size.x = 2;
		size.y = 2;
		size.color = (game->sprite[i]->visible) ? 0x000000 : 0xFF4444;
		ft_rect_filled_borderless(img, start, size);
		i++;
	}
}

void render_sprite_projection(t_game *game, t_img *img){
	t_sprite visible_sprites[game->cubfile->map->num_sprite];
	int num_visible_sprites = 0;
	int i;
	float angle_sprite_player;

	i = 0;
	//Find sprites that are visible (inside the FOV)
	while ( i < game->cubfile->map->num_sprite) {
		angle_sprite_player = ft_normalize_angle(game->player->rotation_angle)
		- atan2(game->sprite[i]->y - game->player->y, game->sprite[i]->x - game->player->x);

		//make sure the angle is always between 0 and 180 degree - Create func
		if (angle_sprite_player > PI)
			angle_sprite_player -= TWO_PI;
		if (angle_sprite_player < -PI)
			angle_sprite_player += TWO_PI;
		angle_sprite_player = fabs(angle_sprite_player);
		// end func
		//margem de erro para o sprite não sumir do nada
		const float EPSILON = 0.2; //adicionar no header
		if (angle_sprite_player < (ft_degtorad(FOV_ANGLE) / 2) + EPSILON) {
			// create func

			t_point start;
			t_point end;

			start.x = game->sprite[i]->x;
			start.y = game->sprite[i]->y;
			end.x = game->player->x;
			end.y = game->player->y;

			game->sprite[i]->visible = TRUE;
			game->sprite[i]->angle = angle_sprite_player;
			game->sprite[i]->distance = ft_distance_between_points(start, end);
			visible_sprites[num_visible_sprites] = *game->sprite[i];
			//end func
			num_visible_sprites++;
		}
		else {
			game->sprite[i]->visible = FALSE;
		}
		i++;
	}

	// sort algo
	int s;
	int q;

	s = 0;
	q = 0;
	while (s < num_visible_sprites - 1) {
		q = s + 1;
		while (q < num_visible_sprites) {
			if (visible_sprites[s].distance < visible_sprites[q].distance) {
				t_sprite temp = visible_sprites[s];
				visible_sprites[s] = visible_sprites[q];
				visible_sprites[q] = temp;
			}
			q++;
		}
		s++;
	}
	//end sort

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

		// Width and height of the sprite texture
		int texture_width = game->sprite_tex->width;
		// int texture_height = game->sprite_tex->height;

		// Loop alll the x values
		float x;
		float y;
		int color;
		t_point texture;

		x = sprite_left_x;
		y = sprite_top_y;
		color = 0;
		while (x < sprite_right_x) {
			float texel_width = (texture_width / sprite_width);

			texture.x = (x - sprite_left_x) * texel_width;
			// printf("%f\n", texture.x);

			while (y < sprite_bottom_y) {
				if (x > 0 && x < game->cubfile->width
				&& y > 0 && y < game->cubfile->height){
					int distance_from_top = y + (sprite_height / 2)
					- (game->cubfile->height / 2);

					texture.y = distance_from_top
					* (game->sprite_tex->height / sprite_height);

					color = ft_texture_byte(game->sprite_tex, texture);
					// if (sprite.distance < game->rays[(int)x]->distance
					// && color != (int)0xff000000)
					if (color != (int)0xff000000)
						my_mlx_pixel_put(img, x, y, color);
					// printf("%i\n", color);
				}
				y++;
			}
			y = sprite_top_y;
			x++;
		}
		w++;
	}

	// end func
	printf("%f\n", game->player->rotation_angle);

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
	if (game->cubfile->map->num_sprite > 0)
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
	if (game->cubfile->map->num_sprite > 0){
		ft_get_all_sprites_pos(game);
		render_sprite_projection(game, game->frame);
	}
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
