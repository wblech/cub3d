/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:54:25 by wbertoni          #+#    #+#             */
/*   Updated: 2020/12/26 13:48:20 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_point	ft_cast_ray(t_game *game, t_hrc join, float ray_angle,
							int is_vert)
{
	float		next_x;
	float		next_y;
	float		x_to_check;
	float		y_to_check;

	next_x = join.intercept.x;
	next_y = join.intercept.y;
	while (!is_end_window(game, next_x, next_y))
	{
		x_to_check = get_x_to_check(next_x, ray_angle, is_vert);
		y_to_check = get_y_to_check(next_y, ray_angle, is_vert);
		if (ft_has_wall(game, x_to_check, y_to_check, '1'))
		{
			return (ft_create_point(next_x, next_y, 1));
			break ;
		}
		else
		{
			next_x += join.step.x;
			next_y += join.step.y;
		}
	}
	return (ft_create_point(0, 0, 0));
}

static	t_point	ft_horz_intercept(t_game *game, float ray_angle)
{
	t_hrc join;

	join.intercept.y = floor(game->player->y / g_tile_size) * g_tile_size;
	join.intercept.y += ft_calc_facing(ray_angle, down) ? g_tile_size : 0;
	join.intercept.x = game->player->x + (join.intercept.y - game->player->y)
	/ tan(ray_angle);
	join.step.y = g_tile_size;
	join.step.y *= ft_calc_facing(ray_angle, up) ? -1 : 1;
	join.step.x = g_tile_size / tan(ray_angle);
	join.step.x *= (ft_calc_facing(ray_angle, left) && join.step.x > 0) ? -1
	: 1;
	join.step.x *= (ft_calc_facing(ray_angle, right) && join.step.x < 0) ? -1
	: 1;
	return (ft_cast_ray(game, join, ray_angle, 0));
}

static	t_point	ft_vert_intercept(t_game *game, float ray_angle)
{
	t_hrc join;

	join.intercept.x = floor(game->player->x / g_tile_size) * g_tile_size;
	join.intercept.x += ft_calc_facing(ray_angle, right) ? g_tile_size : 0;
	join.intercept.y = game->player->y + (join.intercept.x - game->player->x)
	* tan(ray_angle);
	join.step.x = g_tile_size;
	join.step.x *= ft_calc_facing(ray_angle, left) ? -1 : 1;
	join.step.y = g_tile_size * tan(ray_angle);
	join.step.y *= ft_calc_facing(ray_angle, up) && join.step.y > 0 ? -1 : 1;
	join.step.y *= ft_calc_facing(ray_angle, down) && join.step.y < 0 ? -1 : 1;
	return (ft_cast_ray(game, join, ray_angle, 1));
}

static	t_ray	*ft_create_ray(t_game *game, t_point hint, t_point vint)
{
	t_ray		*ray;
	t_point		start;
	float		disth;
	float		distv;

	start = ft_create_point(game->player->x, game->player->y, 0);
	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	disth = hint.color ? ft_distance_between_points(start, hint) : INT_MAX;
	distv = vint.color ? ft_distance_between_points(start, vint) : INT_MAX;
	ray->wall_hit_x = (disth < distv) ? hint.x : vint.x;
	ray->wall_hit_y = (disth < distv) ? hint.y : vint.y;
	ray->distance = (disth < distv) ? disth : distv;
	ray->was_wall_hit_vertical = (disth <= distv) ? 0 : 1;
	return (ray);
}

int				ft_raycast(t_game *game)
{
	float	ray_angle;
	float	num_ray;
	t_ray	**rays;
	int		i;

	i = 0;
	num_ray = game->cubfile->width / WALL_STRIP_WIDTH;
	ray_angle = game->player->rotation_angle - (ft_degtorad(FOV_ANGLE) / 2);
	rays = (t_ray **)malloc(num_ray * sizeof(t_ray));
	if (!rays)
		return (0);
	while (i < num_ray)
	{
		ray_angle = ft_normalize_angle(ray_angle);
		game->ray_width = i;
		rays[i] = ft_create_ray(game, ft_horz_intercept(game, ray_angle),
		ft_vert_intercept(game, ray_angle));
		if (!rays[i])
			return (0);
		rays[i]->ray_angle = ray_angle;
		ray_angle += ft_degtorad(FOV_ANGLE) / num_ray;
		i++;
	}
	ft_helper_rc(game, rays);
	return (1);
}
