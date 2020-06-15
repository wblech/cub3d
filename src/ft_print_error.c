/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:10:48 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/13 22:23:08 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_print_error(t_error error)
{
	if (error == eallow)
		printf("Error\nSymbols allowed for map, without quote,\
' ', '0', '1', '2'. The map inside cubfile must be at the end\n");
	else if (error == enull)
		printf("Error\nMalloc error\n");
	else if (error == ewall)
		printf("Error\nThe map must be closed/surrounded by wall\n");
	else if (error == eempty)
		printf("Error\nThe map can´t have empty lines\n");
	else if (error == erespos)
		printf("Error:\nResolution width and height must be positive \
numbers\n");
	else if (error == eresarg)
		printf("Error:\nNeed 2 arguments for resolution in cub file\n");
	else if (error == epathtex)
		printf("Error:\nNeed to inform path to the texture\n");
	else if (error == ecolortex)
		printf("Error:\nNeed to inform a color to the texture\n");
	else if (error == ergbsize)
		printf("Error:\nRGB color must have 3 values from 0 - 255 separatede \
by a ','\n");
	else if (error == enores)
		printf("Error:\nCouldn´t find  resolution information in cubfile\n");
	else if (error == enotexture)
		printf("Error:\nCouldn´t find  texture information in cubfile\n");
	else if (error == enocolor)
		printf("Error:\nCouldn´t find  color information for ceiling or floor in cubfile\n");
	else if (error == enomap)
		printf("Error:\nCouldn´t find map information in cubfile\n");
	else if (error == eplayer)
		printf("Error:\nCouldn´t find initial player position on the map\n");

}
