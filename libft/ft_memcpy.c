/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:25:35 by wbertoni          #+#    #+#             */
/*   Updated: 2020/02/07 15:59:15 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	size_t				i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (dst != src && i < n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (dst);
}
