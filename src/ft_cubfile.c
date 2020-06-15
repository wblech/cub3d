/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cubfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 23:45:35 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/15 00:11:36 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_del_line(char **line)
{
	free(*line);
	free(line);
}

static int ft_read_cubfile(t_vars *vars, t_file *file, int fopen)
{
	t_error e;
	char **line;
	int ret;

	line = (char **)malloc(sizeof(char));
	if (!line)
		return (FALSE);
	while ((ret = get_next_line(fopen, line)))
	{
		if (ret < 0)
			return (FALSE);
		if ((e = ft_get_cubfile_value(vars, file, *line)) != noerror)
		{
			ft_print_error(e);
			ft_del_line(line);
			return (FALSE);
		}
	}
	ft_del_line(line);
	return (TRUE);
}

t_file *ft_create_file_struct(void)
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
	return (file);
}

t_file *ft_cubfile(t_vars *vars, char *cubfile)
{
	int fopen;
	t_file *file;
	t_error e;

	e = enull;
	file = ft_create_file_struct();
	if (!file || (e = ft_malloc_file_map(file)) != noerror)
	{
		ft_print_error(e);
		return (NULL);
	}
	fopen = open(cubfile, O_RDONLY);
	if (fopen < 0)
	{
		perror("Error\n");
		return (NULL);
	}
	if (!ft_read_cubfile(vars, file, fopen))
		return (NULL);
	if (!ft_cubfile_check_and_get_function(file))
		return (NULL);
	return (file);
}
