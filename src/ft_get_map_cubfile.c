/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_cubfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 17:21:14 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/09 18:05:58 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_new_row(t_map *map, char *line, const int i, int j)
{
	while (j < map->num_col && line[j] != '\0')
	{
		map->map[i][j] = line[j];
		j++;
	}
}

static int ft_first_row(t_map *map, char *line, int size)
{
	int j;

	j = 0;
	map->num_row++;
	map->num_col = size;
	map->map = ft_malloc_map(map->num_row, map->num_col);
	if (!map->map)
		return (FALSE);
	ft_new_row(map, line, 0, j);
	return (TRUE);
}

static int ft_mapcpy(t_map *map, char **tmp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	map->map = ft_malloc_map(map->num_row, map->num_col);
	if (!map->map)
		return (FALSE);
	while (i < map->num_row - 1)
	{
		while (j < map->num_col)
		{
			if (tmp[i][j] != '\0')
				map->map[i][j] = tmp[i][j];
			else
				break;
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}

t_error ft_get_map_cubfile(t_file *file, char *line)
{
	int size;
	int i;
	int j;
	char **tmp;

	j = 0;
	i = 0;
	size = (int)ft_strlen(line);
	if (file->map->num_row == 0)
	{
		if (!ft_first_row(file->map, line, size))
			return (enull);
	}
	else
	{
		tmp = file->map->map;
		if (size > file->map->num_col)
			file->map->num_col = size;
		file->map->num_row++;
		if (!(i = ft_mapcpy(file->map, tmp)))
			return (enull);
		ft_free_map(tmp);
		ft_new_row(file->map, line, i, j);
	}
	return (noerror);
}
