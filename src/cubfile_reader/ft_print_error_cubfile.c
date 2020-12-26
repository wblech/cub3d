/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error_cubfile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:00:22 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/12 12:06:55 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putstr(char *str)
{
	int counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		ft_putchar(str[counter]);
		counter++;
	}
}

static void		ft_print_error_cubfile_norminette(t_error_file error)
{
	if (error == enotexture)
		ft_putstr("Error:\nCouldn´t find  texture information in cubfile\n");
	else if (error == enocolor)
		ft_putstr("Error:\nCouldn´t find  color information for ceiling or \
		floor in cubfile\n");
	else if (error == enomap)
		ft_putstr("Error:\nCouldn´t find map information in cubfile\n");
	else if (error == eplayer)
		ft_putstr("Error:\nCouldn´t find initial player position on the map\n");
}

void			ft_print_error_cubfile(t_error_file error)
{
	if (error == eallow)
		ft_putstr("Error\nSymbols allowed for map, without quote,\
' ', '0', '1', '2'. The map inside cubfile must be at the end\n");
	else if (error == enull)
		ft_putstr("Error\nMalloc error\n");
	else if (error == ewall)
		ft_putstr("Error\nThe map must be closed/surrounded by wall\n");
	else if (error == eempty)
		ft_putstr("Error\nThe map can´t have empty lines\n");
	else if (error == erespos)
		ft_putstr("Error:\nResolution width and height must be positive \
numbers\n");
	else if (error == eresarg)
		ft_putstr("Error:\nNeed 2 arguments for resolution in cub file\n");
	else if (error == epathtex)
		ft_putstr("Error:\nNeed to inform path to the texture\n");
	else if (error == ecolortex)
		ft_putstr("Error:\nNeed to inform a color to the texture\n");
	else if (error == ergbsize)
		ft_putstr("Error:\nRGB color must have 3 values from 0 - 255 separated \
by a ','\n");
	else if (error == enores)
		ft_putstr("Error:\nCouldn´t find  resolution information in cubfile\n");
	else
		ft_print_error_cubfile_norminette(error);
}
