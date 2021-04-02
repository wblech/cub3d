/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info_value_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:00:11 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/01 18:03:22 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

t_error_file	ft_get_texture_path_norminette(t_file *file, char **info)
{
	if ((ft_strncmp("NO", info[0], 3) == 0) && !file->north)
		file->north = ft_strdup(info[1]);
	else if (ft_strncmp("NO", info[0], 3) == 0)
		return (erepeat);
	else if ((ft_strncmp("SO", info[0], 3) == 0) && !file->south)
		file->south = ft_strdup(info[1]);
	else if (ft_strncmp("SO", info[0], 3) == 0)
		return (erepeat);
	else if ((ft_strncmp("WE", info[0], 3) == 0) && !file->west)
		file->west = ft_strdup(info[1]);
	else if (ft_strncmp("WE", info[0], 3) == 0)
		return (erepeat);
	else if ((ft_strncmp("EA", info[0], 3) == 0) && !file->east)
		file->east = ft_strdup(info[1]);
	else if (ft_strncmp("EA", info[0], 3) == 0)
		return (erepeat);
	else if ((ft_strncmp("S", info[0], 3) == 0) && !file->sprite)
		file->sprite = ft_strdup(info[1]);
	else if (ft_strncmp("S", info[0], 3) == 0)
		return (erepeat);
	return (noerror);
}
