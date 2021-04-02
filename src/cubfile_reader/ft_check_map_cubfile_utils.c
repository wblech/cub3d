/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_cubfile_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:22:06 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 10:27:11 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

/*
** w = wall
** s = space
*/

int			ft_is_w_or_s(int c)
{
	if (c == '1' || c == ' ')
		return (TRUE);
	return (FALSE);
}

static int	ft_is_empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int			ft_check_map_cubfile_has_empty_line(char **line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i][0] == ' ')
		{
			if (ft_is_empty_line(line[i]))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int			ft_check_diagonal_map_surronded(t_map *map)
{
		int		i;
	int		j;
	t_face	direction;

	direction = up;
	i = 0;
	j = 0;
	while (map->map[i] != '\0')
	{
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] != '1' && map->map[i][j] != ' ')
			{
				if (map->map[i-1][j-1] == ' ')
					return (FALSE);
				else if (map->map[i-1][j+1] == ' ')
					return (FALSE);
				else if (map->map[i+1][j-1] == ' ')
					return (FALSE);
				else if (map->map[i+1][j+1] == ' ')
					return (FALSE);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (TRUE);
}
