/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:01:23 by wbertoni          #+#    #+#             */
/*   Updated: 2021/03/30 19:38:14 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex		*ft_create_texture(void *mlx_ptr, char *path)
{
	t_tex	*texture;
	t_img	*img;

	texture = (t_tex *)malloc(sizeof(t_tex));
	img = (t_img *)malloc(sizeof(t_img));
	if (!texture || !img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
	&texture->height);
	if (!img->img)
		return (NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
	&img->line_length, &img->endian);
	texture->img = img;
	return (texture);
}

int			ft_texture_byte(t_tex *texture, t_point pos)
{
	char	*color;
	int		y;
	int		x;

	y = (int)pos.y;
	x = (int)pos.x;
	color = texture->img->addr + (y * texture->img->line_length + x
	* (texture->img->bits_per_pixel / 8));
	return (*(unsigned int*)color);
}

int			ft_get_texture_color(t_game *game, float wall_height, int index,
int y)
{
	int		dist_from_top;
	int		x_texture;
	int		y_texture;
	t_point	texture;

	x_texture = (!game->rays[index]->was_wall_hit_vertical)
							? (int)game->rays[index]->wall_hit_x % TILE_SIZE
							: (int)game->rays[index]->wall_hit_y % TILE_SIZE;
	dist_from_top = y + (wall_height / 2) - (game->cubfile->height / 2);
	y_texture = dist_from_top * ((float)game->tex_def->height / wall_height);
	texture.x = x_texture;
	texture.y = y_texture;
	if (ft_calc_facing(game->rays[index]->ray_angle, left)
	&& game->rays[index]->was_wall_hit_vertical)
		return (ft_texture_byte(game->west, texture));
	else if (ft_calc_facing(game->rays[index]->ray_angle, right)
	&& game->rays[index]->was_wall_hit_vertical)
		return (ft_texture_byte(game->east, texture));
	else if (ft_calc_facing(game->rays[index]->ray_angle, up)
	&& !game->rays[index]->was_wall_hit_vertical)
		return (ft_texture_byte(game->north, texture));
	else if (ft_calc_facing(game->rays[index]->ray_angle, down)
	&& !game->rays[index]->was_wall_hit_vertical)
		return (ft_texture_byte(game->south, texture));
	return (ft_texture_byte(game->tex_def, texture));
}
