/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:30:13 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 08:58:47 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	ft_is_cub(char *str)
{
	size_t i;

	i = ft_strlen(str) - 4;
	if (ft_memcmp(&str[i], ".cub", 4))
		return (0);
	return (1);
}

int			check_args(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putstr("No argument");
		exit(0);
	}
	else if (argc > 3)
	{
		ft_putstr("Too many arguments");
		exit(0);
	}
	else if (!(ft_is_cub(argv[1])))
	{
		ft_putstr("First argument is not .cub");
		exit(0);
	}
	else if (argc == 3 && ft_memcmp(argv[2], "--save", 7))
	{
		ft_putstr("Second argument is invalid. Try --save");
		exit(0);
	}
	return (0);
}
