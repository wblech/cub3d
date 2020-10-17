/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 23:40:30 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/17 15:29:25 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

void			ft_del_info(char **info)
{
	int i;

	i = 0;
	while (info[i] != '\0')
	{
		free(info[i]);
		i++;
	}
	free(info);
}

static t_error_file	ft_get_ceiling_floor_color(t_file *file, char **info)
{
	char			**rgb;
	int				size;
	t_error_file	error;

	size = 0;
	error = noerror;
	while (info[size] != '\0')
		size++;
	if (size < 2)
		return (ecolortex);
	rgb = ft_split(info[1], ',');
	size = 0;
	while (rgb[size] != '\0')
		size++;
	if (size < 3)
		error = ergbsize;
	else if (ft_strncmp("F", info[0], 3) == 0)
		file->floor = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8
		| ft_atoi(rgb[2]);
	else if (ft_strncmp("C", info[0], 3) == 0)
		file->ceiling = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8
		| ft_atoi(rgb[2]);
	ft_del_info(rgb);
	return (error);
}

static t_error_file	ft_get_texture_path(t_file *file, char **info)
{
	int size;

	size = 0;
	while (info[size] != '\0')
		size++;
	if (size < 2)
		return (epathtex);
	if ((ft_strncmp("NO", info[0], 3) == 0))
		file->north = ft_strdup(info[1]);
	else if ((ft_strncmp("SO", info[0], 3) == 0))
		file->south = ft_strdup(info[1]);
	else if ((ft_strncmp("WE", info[0], 3) == 0))
		file->west = ft_strdup(info[1]);
	else if ((ft_strncmp("EA", info[0], 3) == 0))
		file->east = ft_strdup(info[1]);
	else if ((ft_strncmp("S", info[0], 3) == 0))
		file->sprite = ft_strdup(info[1]);
	return (noerror);
}

static t_error_file	ft_get_resolution(t_file *file, char **info)
{
	int size;

	size = 0;
	while (info[size] != '\0')
		size++;
	if (size < 3)
		return (eresarg);
	if (!ft_isdigit(info[1][0]) || !ft_isdigit(info[2][0]))
		return (erespos);
	file->width = ft_atoi(info[1]);
	file->height = ft_atoi(info[2]);
	return (noerror);
}

t_error_file		ft_get_info_value(t_file *file, char **info)
{
	t_error_file e;

	e = noerror;
	if (ft_strncmp("R", info[0], 3) == 0)
		e = ft_get_resolution(file, info) != noerror;
	else if ((ft_strncmp("NO", info[0], 3) == 0)
	|| (ft_strncmp("SO", info[0], 3) == 0)
	|| (ft_strncmp("WE", info[0], 3) == 0)
	|| (ft_strncmp("EA", info[0], 3) == 0)
	|| (ft_strncmp("S", info[0], 3) == 0))
		e = ft_get_texture_path(file, info) != noerror;
	else if ((ft_strncmp("F", info[0], 3) == 0)
	|| (ft_strncmp("C", info[0], 3) == 0))
		e = ft_get_ceiling_floor_color(file, info) != noerror;
	return (e);
}
