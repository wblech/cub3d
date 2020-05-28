/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:40:19 by wbertoni          #+#    #+#             */
/*   Updated: 2020/05/28 15:32:10 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_count = 0;

t_map *ft_fake_map()
{
	t_map *map_clone;
	int i_row;
	int i_col;
	int map[11][15] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	i_row = 0;
	i_col = 0;
	map_clone = malloc(sizeof(t_map));
	map_clone->num_col = 15;
	map_clone->num_row = 11;
	map_clone->map = malloc(map_clone->num_row * sizeof(int *));

	while (i_row < map_clone->num_row)
	{
		map_clone->map[i_row] = (int *)malloc(map_clone->num_col * sizeof(int));
		while (i_col < map_clone->num_col)
		{
			map_clone->map[i_row][i_col] = map[i_row][i_col];
			i_col++;
		}
		i_col = 0;
		i_row++;
	}
	return (map_clone);
}

// void ft_raycast_render(t_vars *vars, t_data *img)
void ft_draw_2d_map(t_vars *vars, t_data *img)
{
	int i;
	t_point central;
	t_point end;

	i = 0;
	central = ft_create_point(MINIMAP_SCALE_FACTOR * vars->player->x,
							  MINIMAP_SCALE_FACTOR * vars->player->y, 0x00ff0000);
	ft_create_2d_map(img, vars->map);
	ft_circle_filled(img, central, vars->player->radius);
	while (i < (vars->win_width / WALL_STRIP_WIDTH))
	{
		end = ft_create_point(MINIMAP_SCALE_FACTOR * vars->rays[i]->wall_hit_x,
							  MINIMAP_SCALE_FACTOR * vars->rays[i]->wall_hit_y,
							  0x00ff0000);
		ft_line_dda(img, central, end);
		i++;
	}
}



t_tex *ft_get_texture(void *mlx_ptr, char *path)
{
	t_tex *texture;
	t_data *img;

	texture = (t_tex *)malloc(sizeof(t_tex));
	img = (t_data *)malloc(sizeof(t_data));
	img->img = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
	&texture->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
	&img->line_length, &img->endian);
	texture->img = img;
	return (texture);
}

int get_texture_color (t_tex *texture, t_point pos)
{
	int offset;
	int a;
	int r;
	int g;
	int b;

	offset = pos.y * texture->img->line_length
	+ pos.x * (texture->img->bits_per_pixel / 8);
	a = texture->img->addr[offset + 0];
	r = texture->img->addr[offset + 1];
	g = texture->img->addr[offset + 2];
	b = texture->img->addr[offset + 3];
	return (b << 24 | g << 16 | r << 8 | a);
}

float ft_map(int x, int in_min, int in_max, int out_min, int out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ft_draw_3d_map(t_vars *vars, t_data *img)
{
	float player_distance;
	float wall_height;
	t_point start;
	t_point size;
	float wall_top;
	float wall_bottom;
	int i;

	i = 0;
	player_distance = (vars->win_width / 2) / tan(ft_degtorad(FOV_ANGLE / 2));
	while (i < (vars->win_width / WALL_STRIP_WIDTH))
	{
		float perpDistance = vars->rays[i]->distance * cos(vars->rays[i]->ray_angle - vars->player->rotation_angle);
		wall_height = (TILE_SIZE / perpDistance) * player_distance;
		wall_top = (vars->win_height / 2) - (wall_height / 2);
		wall_top = (wall_top < 0) ? 0 : wall_top;
		wall_bottom = (vars->win_height / 2) + (wall_height / 2);
		// wall_bottom = (wall_height > vars->win_height) ? vars->win_height : wall_height;
		wall_bottom = (wall_bottom > vars->win_height) ? vars->win_height : wall_bottom;
		//topo
		if (wall_top > 0)
			ft_rect_filled_borderless(img, ft_create_point(i * WALL_STRIP_WIDTH, 0, 0xFFFf0000), ft_create_point(WALL_STRIP_WIDTH, wall_top, 0xFFFf0000));
		int color2;
		int color = vars->rays[i]->was_wall_hit_vertical ? 0x00ff00 : 0x808080;
		start = ft_create_point(i * WALL_STRIP_WIDTH, wall_top, color);
		size = ft_create_point(WALL_STRIP_WIDTH, wall_bottom, color);
		int tex_offset = (int)vars->rays[i]->wall_hit_x % TILE_SIZE;
		t_point pos;
		pos.x = tex_offset;
		pos.y = 0;
		int d = 0;
		int j = 0;
		int y = wall_top;

		while (d < WALL_STRIP_WIDTH)
		{
			// while (j < size.y)
			while (j < wall_bottom - wall_top)
			{
				pos.y = (int)ft_map(start.y + j, wall_top, wall_bottom, 0, 63) % (int)TILE_SIZE;
				// printf("%f\n", (float)vars->texture->height / wall_height);
				// printf("(%f, %f)\n", pos.x, pos.y);
				color2 = get_texture_color(vars->texture, pos);
				color2 = vars->rays[i]->was_wall_hit_vertical ? 0x00ff00 : color2;
				my_mlx_pixel_put(img, start.x + d, start.y + j, color2);
				y++;
				j++;
			}
			j = 0;
			d++;
		}
		i++;
	}
}

void ft_setup(t_vars *vars)
{
	t_map *map;

	g_minimap = TRUE;
	map = ft_fake_map();
	ft_create_vars(vars, map);
	ft_raycast(vars);
	ft_draw_2d_map(vars, vars->img);
	ft_draw_3d_map(vars, vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

int main(void)
{
	t_vars vars;
	t_map *map;

	map = ft_fake_map();
	ft_setup(&vars);
	mlx_hook(vars.win, 2, 1L << 0, ft_update_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, ft_update_release, &vars);
	mlx_hook(vars.win, 17, 1L << 17, ft_close, &vars);
	mlx_expose_hook(vars.win, ft_render, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
