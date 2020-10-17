/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:06:00 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/12 12:05:54 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

void	ft_del_map(t_map *map)
{
	int i;

	i = 0;
	if (map != NULL)
	{
		while (i < map->num_row)
		{
			if (map->map[i] != NULL)
				free(map->map[i]);
			i++;
		}
		free(map);
	}
}

void	ft_del_file(t_file *file)
{
	if (file != NULL)
	{
		if (file->north != NULL)
			free(file->north);
		if (file->south != NULL)
			free(file->south);
		if (file->west != NULL)
			free(file->west);
		if (file->east != NULL)
			free(file->east);
		ft_del_map(file->map);
		free(file);
	}
}
