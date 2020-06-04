/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:22:37 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/01 17:12:57 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point ft_cast_ray(t_vars *vars, t_point intercept, t_point step,
					float ray_angle, int is_vert)
{
	float next_x;
	float next_y;
	float x_to_check;
	float y_to_check;
	t_point pos_hit_wall;

	next_x = intercept.x;
	next_y = intercept.y;
	while (!is_end_window(vars, next_x, next_y))
	{
		x_to_check = next_x + ((ft_calc_facing(ray_angle, left) && is_vert) ? -1 : 0);
		y_to_check = next_y + ((ft_calc_facing(ray_angle, up) && !is_vert) ? -1 : 0);
		if (ft_has_wall(vars, x_to_check, y_to_check))
		{
			pos_hit_wall = ft_create_point(next_x, next_y, 1);
			return (pos_hit_wall);
			break;
		}
		else
		{
			next_x += step.x;
			next_y += step.y;
		}
	}
	return (ft_create_point(0, 0, 0));
}

static t_point ft_horz_intercept(t_vars *vars, float ray_angle)
{
	t_point intercept;
	t_point step;

	intercept.y = floor(vars->player->y / TILE_SIZE) * TILE_SIZE;
	intercept.y += ft_calc_facing(ray_angle, down) ? TILE_SIZE : 0;
	intercept.x = vars->player->x + (intercept.y - vars->player->y) / tan(ray_angle);
	step.y = TILE_SIZE;
	step.y *= ft_calc_facing(ray_angle, up) ? -1 : 1;
	step.x = TILE_SIZE / tan(ray_angle);
	step.x *= (ft_calc_facing(ray_angle, left) && step.x > 0) ? -1 : 1;
	step.x *= (ft_calc_facing(ray_angle, right) && step.x < 0) ? -1 : 1;
	return (ft_cast_ray(vars, intercept, step, ray_angle, 0));
}

static t_point ft_vert_intercept(t_vars *vars, float ray_angle)
{
	t_point intercept;
	t_point step;

	intercept.x = floor(vars->player->x / TILE_SIZE) * TILE_SIZE;
	intercept.x += ft_calc_facing(ray_angle, right) ? TILE_SIZE : 0;

	intercept.y = vars->player->y + (intercept.x - vars->player->x) * tan(ray_angle);
	step.x = TILE_SIZE;
	step.x *= ft_calc_facing(ray_angle, left) ? -1 : 1;

	step.y = TILE_SIZE * tan(ray_angle);
	step.y *= ft_calc_facing(ray_angle, up) && step.y > 0 ? -1 : 1;
	step.y *= ft_calc_facing(ray_angle, down) && step.y < 0 ? -1 : 1;
	return (ft_cast_ray(vars, intercept, step, ray_angle, 1));
}


static t_ray *ft_create_ray(t_vars *vars, t_point hint, t_point vint)
{
	t_ray *ray;
	t_point start;
	float disth;
	float distv;

	start = ft_create_point(vars->player->x, vars->player->y, 0);
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

int ft_raycast(t_vars *vars)
{
	float ray_angle;
	float num_ray;
	t_ray **rays;
	int i;

	i = 0;
	num_ray = vars->win_width / WALL_STRIP_WIDTH;
	ray_angle = vars->player->rotation_angle - (ft_degtorad(FOV_ANGLE) / 2);
	rays = (t_ray **)malloc(num_ray * sizeof(t_ray));
	if (!rays)
		return (0);
	while (i < num_ray)
	{
		ray_angle = ft_normalize_angle(ray_angle);
		rays[i] = ft_create_ray(vars, ft_horz_intercept(vars, ray_angle),
		ft_vert_intercept(vars, ray_angle));
		if (!rays[i])
			return (0);
		rays[i]->ray_angle = ray_angle;
		ray_angle += ft_degtorad(FOV_ANGLE) / num_ray;
		i++;
	}
	if (vars->rays != NULL)
		ft_del_rays(vars);
	vars->rays = rays;
	return (1);
}
