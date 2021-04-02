/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 08:51:12 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 08:53:41 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

int	ft_get_size(char **str)
{
	int size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}
