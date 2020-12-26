/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:58:05 by wbertoni          #+#    #+#             */
/*   Updated: 2020/02/04 13:48:32 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (len && (unsigned long)dst > (unsigned long)src)
	{
		i = 1;
		while (src != dst && i <= len)
		{
			*(unsigned char*)(dst + len - i) = *(unsigned char*)(src + len - i);
			i++;
		}
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
