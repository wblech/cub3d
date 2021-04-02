/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ceiling_floor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 08:32:04 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 08:38:51 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

static int	ft_check_is_digit(char **rgb)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		while (rgb[i][j] != '\0')
		{
			if (!ft_isdigit(rgb[i][j]))
				return (FALSE);
			j++;
		}
		j = 0;
		i++;
	}
	return (TRUE);
}

static int	ft_check_is_bigger(char **rgb)
{
	int red;
	int green;
	int blue;

	red = ft_atoi(rgb[0]);
	green = ft_atoi(rgb[1]);
	blue = ft_atoi(rgb[2]);
	if (red < 0 || red > 255
	|| green < 0 || green > 255
	|| blue < 0 || blue > 255)
		return (FALSE);
	return (TRUE);
}

int			ft_check_ceiling_floor(char **rgb)
{
	if (!ft_check_is_digit(rgb))
		return (FALSE);
	if (!ft_check_is_bigger(rgb))
		return (FALSE);
	return (TRUE);
}
