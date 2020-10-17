/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cubfile_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:25:51 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/08 16:42:48 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

static t_error_file		ft_check_cubfile(t_file *file)
{
	if (file->width < 0 || file->height < 0)
		return (enores);
	else if (!file->north || !file->south
	|| !file->west || !file->east || !file->sprite)
		return (enotexture);
	else if (file->floor < 0 || file->ceiling < 0)
		return (enocolor);
	else if (file->map->num_col == 0 && file->map->num_row == 0)
		return (enomap);
	return (noerror);
}

static t_error_file		ft_get_player_position(t_file *file)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (file->map->map[i] != '\0')
	{
		while (file->map->map[i][j] != '\0')
		{
			if (file->map->map[i][j] == 'N'
			|| file->map->map[i][j] == 'S' || file->map->map[i][j] == 'W'
			|| file->map->map[i][j] == 'E')
			{
				file->map->initial_pl_cardinal = file->map->map[i][j];
				file->map->initial_pl_x = j * TILE_SIZE;
				file->map->initial_pl_y = i * TILE_SIZE;
				file->map->map[i][j] = '0';
				return (noerror);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (eplayer);
}

/*
** Possível memoryleak
*/

t_error_file			ft_get_cubfile_value(t_file *file, char *line)
{
	int				i;
	char			**info;
	t_error_file	e;

	i = 0;
	e = noerror;
	while (ft_isspace(line[i]))
		i++;
	if (ft_isdigit(line[i]) || file->map->num_row > 0)
	{
		if ((e = ft_get_map_cubfile(file, line)) != noerror)
			return (e);
	}
	if (file->map->num_row == 0 && line[i] != '\0')
	{
		info = ft_split(line, ' ');
		if ((e = ft_get_info_value(file, info)) != noerror)
			return (e);
	}
	return (noerror);
}

t_error_file			ft_malloc_file_map(t_file *file)
{
	file->map = (t_map *)malloc(sizeof(t_map));
	if (!file->map)
		return (enull);
	file->map->num_col = 0;
	file->map->num_row = 0;
	return (noerror);
}

int						ft_cubfile_check_and_get_function(t_file *file)
{
	t_error_file e;

	if ((e = ft_check_cubfile(file)) != noerror)
	{
		ft_print_error_cubfile(e);
		return (FALSE);
	}
	if ((e = ft_check_map_cubfile(file->map)) != noerror)
	{
		ft_print_error_cubfile(e);
		return (FALSE);
	}
	if ((e = ft_get_player_position(file)) != noerror)
	{
		ft_print_error_cubfile(e);
		return (FALSE);
	}
	return (TRUE);
}
