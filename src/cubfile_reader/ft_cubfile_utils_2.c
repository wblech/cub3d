/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cubfile_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:10:53 by wbertoni          #+#    #+#             */
/*   Updated: 2021/03/28 19:11:14 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

t_error_file	ft_check_cubfile(t_file *file)
{
	if (file->width < 0 || file->height < 0)
		return (enores);
	else if (!file->north || !file->south || !file->west
	|| !file->east || !file->sprite)
		return (enotexture);
	else if (file->floor < 0 || file->ceiling < 0)
		return (enocolor);
	else if (file->map->num_col == 0 && file->map->num_row == 0)
		return (enomap);
	return (noerror);
}
