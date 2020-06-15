/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_cubfile_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:22:06 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/12 16:07:21 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_is_wall_or_space(int c)
{
	if (c == '1' || c == ' ')
		return (TRUE);
	return (FALSE);
}

static int ft_is_empty_line(char *line)
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

int ft_check_map_cubfile_has_empty_line(char **line)
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
