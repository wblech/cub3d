/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_player_doubled.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:07:19 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/01 19:08:07 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

t_error_file	ft_is_player_doubled(t_file *file)
{
	int i;
	int j;
	int counter;

	i = 0;
	j = 0;
	counter = 0;
	while (file->map->map[i] != '\0')
	{
		while (file->map->map[i][j] != '\0')
		{
			if (file->map->map[i][j] == 'N' || file->map->map[i][j] == 'S'
			|| file->map->map[i][j] == 'W' || file->map->map[i][j] == 'E')
			{
				if (counter == 0)
					counter++;
				else
					return (epldoubled);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (noerror);
}
