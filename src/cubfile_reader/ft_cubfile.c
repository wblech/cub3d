/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cubfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:45:43 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/12 12:05:07 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

static void		ft_del_line(char **line)
{
	free(*line);
	free(line);
}

static int		ft_read_cubfile(t_file *file, int fopen)
{
	t_error_file	e;
	char			**line;
	int				ret;

	line = (char **)malloc(sizeof(char *));
	if (!line)
		return (FALSE);
	while ((ret = get_next_line(fopen, line)))
	{
		if (ret < 0)
			return (FALSE);
		if ((e = ft_get_cubfile_value(file, *line)) != noerror)
		{
			ft_print_error_cubfile(e);
			ft_del_line(line);
			return (FALSE);
		}
	}
	ft_del_line(line);
	return (TRUE);
}

t_file			*ft_create_file_struct(void)
{
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->width = -1;
	file->height = -1;
	file->north = NULL;
	file->south = NULL;
	file->west = NULL;
	file->east = NULL;
	file->sprite = NULL;
	file->floor = -1;
	file->ceiling = -1;
	file->map = NULL;
	return (file);
}

int				ft_count_sprite(t_map *map)
{
	int count;
	int i;
	int j;

	i = 0;
	j = 0;
	count = 0;
	while (i < map->num_row)
	{
		while (j < map->num_col)
		{
			if (map->map[i][j] == '2')
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	return (count);
}

t_file			*ft_cubfile(char *cubfile)
{
	int				fopen;
	t_file			*file;
	t_error_file	e;

	e = enull;
	file = ft_create_file_struct();
	if (!file || (e = ft_malloc_file_map(file)) != noerror)
	{
		ft_print_error_cubfile(e);
		return (NULL);
	}
	fopen = open(cubfile, O_RDONLY);
	if (fopen < 0)
	{
		perror("Error\n");
		return (NULL);
	}
	if (!ft_read_cubfile(file, fopen))
		return (NULL);
	if (!ft_cubfile_check_and_get_function(file))
		return (NULL);
	file->map->num_sprite = ft_count_sprite(file->map);
	return (file);
}
