/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ray_once.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 11:52:21 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 11:57:45 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_create_ray_once(t_game *game)
{
	t_ray	**rays;
	float	num_ray;
	int		i;

	i = 0;
	num_ray = game->cubfile->width / WALL_STRIP_WIDTH;
	rays = (t_ray **)malloc(num_ray * sizeof(t_ray));
	if (!rays)
		return (FALSE);
	while (i < num_ray)
	{
		rays[i] = (t_ray *)malloc(sizeof(t_ray));
		if (!rays)
			return (FALSE);
		i++;
	}
	game->rays = rays;
	return (TRUE);
}
