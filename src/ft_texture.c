/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:35:03 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/03 15:48:07 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex		*ft_create_texture(void *mlx_ptr, char *path)
{
	t_tex	*texture;
	t_data	*img;

	texture = (t_tex *)malloc(sizeof(t_tex));
	img = (t_data *)malloc(sizeof(t_data));
	if (!texture || !img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
	&texture->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
	&img->line_length, &img->endian);
	texture->img = img;
	return (texture);
}

static int	ft_texture_byte(t_tex *texture, t_point pos)
{
	int offset;
	int a;
	int r;
	int g;
	int b;

	offset = pos.y * texture->img->line_length + pos.x
	* (texture->img->bits_per_pixel / 8);
	a = texture->img->addr[offset + 0];
	r = texture->img->addr[offset + 1];
	g = texture->img->addr[offset + 2];
	b = texture->img->addr[offset + 3];
	return (b << 24 | g << 16 | r << 8 | a);
}

int			ft_get_texture_color(t_vars *vars, float wall_height, int index,
int y)
{
	int		distanceFromTop;
	int		x_texture;
	int		y_texture;
	t_point texture;

	x_texture = (!vars->rays[index]->was_wall_hit_vertical) ? (int)vars->rays[index]->wall_hit_x % TILE_SIZE : (int)vars->rays[index]->wall_hit_y % TILE_SIZE;
	distanceFromTop = y + (wall_height / 2) - (vars->win_height / 2);
	y_texture = distanceFromTop * ((float)vars->texture->height / wall_height);
	texture.x = x_texture;
	texture.y = y_texture;
	if (ft_calc_facing(vars->rays[index]->ray_angle, left)
	&& vars->rays[index]->was_wall_hit_vertical)
		return (ft_texture_byte(vars->file->west, texture));
	else if (ft_calc_facing(vars->rays[index]->ray_angle, right)
	&& vars->rays[index]->was_wall_hit_vertical)
		return (ft_texture_byte(vars->file->east, texture));
	else if (ft_calc_facing(vars->rays[index]->ray_angle, up)
	&& !vars->rays[index]->was_wall_hit_vertical)
		return (ft_texture_byte(vars->file->north, texture));
	else if (ft_calc_facing(vars->rays[index]->ray_angle, down)
	&& !vars->rays[index]->was_wall_hit_vertical)
		return (ft_texture_byte(vars->file->south, texture));
	return (ft_texture_byte(vars->texture, texture));
}
