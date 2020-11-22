/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:52:06 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/22 11:09:11 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_pointer_null(void *ptr)
{
	return (!ptr ? TRUE : FALSE);
}

int	ft_get_error(int (*func)(void *), void *a, char *msg)
{
	int is_true;

	is_true = func(a);
	if (is_true)
		ft_putstr(msg);
	return (is_true);
}
