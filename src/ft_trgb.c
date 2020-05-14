/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:59:20 by wbertoni          #+#    #+#             */
/*   Updated: 2020/04/27 17:00:08 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Function : create_trgb
** ----------
** Description: gets an ARGB value and returns an integer to be stored in
** the bit_per_pixel format
**
** t = the transparency from 0 to 255
** r = red value from 0 to 255
** g = green value from 0 to 255
** b = blue value from 0 to 255
**
** Return: An integer representing in bits the color
**
*/

int	create_trgb(int t, int r, int g, int b)
{
	return(b << 24 | g << 16 | r << 8 | t);
}

/*
** Functions: get_t, get_r, get_g, get_b
** -----------
** Description: These functions get the value of the color (red, green or blue)
** or of the transparency inside the color argument.
**
** color: the value returned from the function create_trgb
**
** Return: the integer between 0 - 255 realted to the color or transparency from
** the paramenter
*/

int get_t(int trgb)
{
	return (trgb & 0xFF);
}

int get_r(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int get_g(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int get_b(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}
