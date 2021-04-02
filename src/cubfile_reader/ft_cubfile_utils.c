/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cubfile_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:25:51 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 08:44:02 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

static t_error_file	ft_get_player_position_cubfile(t_file *file)
{
	int				i;
	int				j;
	t_error_file	e;

	i = 0;
	j = 0;
	e = noerror;
	if ((e = ft_is_player_doubled(file)) != noerror)
		return (e);
	while (file->map->map[i] != '\0')
	{
		while (file->map->map[i][j] != '\0')
		{
			if (file->map->map[i][j] == 'N' || file->map->map[i][j] == 'S'
			|| file->map->map[i][j] == 'W' || file->map->map[i][j] == 'E')
			{
				ft_set_player_position(file, i, j);
				return (e);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (eplayer);
}

t_error_file		ft_only_space(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t' || line[i] == '\n' || line[i] == '\v'
		|| line[i] == '\f' || line[i] == '\r')
			return (espace);
		i++;
	}
	return (noerror);
}

t_error_file		ft_get_cubfile_value(t_file *file, char *line)
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
	if ((e = ft_only_space(line)) == espace)
		return (e);
	if (file->map->num_row == 0 && line[i] != '\0')
	{
		info = ft_split(line, ' ');
		e = ft_get_info_value(file, info);
		ft_del_info(info);
	}
	return (e);
}

t_error_file		ft_malloc_file_map(t_file *file)
{
	file->map = (t_map *)malloc(sizeof(t_map));
	if (!file->map)
		return (enull);
	file->map->map = NULL;
	file->map->num_col = 0;
	file->map->num_row = 0;
	return (noerror);
}

int					ft_cubfile_check_and_get_function(t_file *file)
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
	if ((e = ft_get_player_position_cubfile(file)) != noerror)
	{
		ft_print_error_cubfile(e);
		return (FALSE);
	}
	return (TRUE);
}
