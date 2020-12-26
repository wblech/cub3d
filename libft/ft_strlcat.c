/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:16:02 by wbertoni          #+#    #+#             */
/*   Updated: 2020/02/04 14:23:28 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_src = 0;
	len_dst = 0;
	while (src[len_src] != '\0')
		len_src++;
	while (dst[len_dst] != '\0' && len_dst < dstsize)
		len_dst++;
	i = len_dst;
	while (dstsize && src[i - len_dst] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i - len_dst];
		i++;
	}
	if (len_dst < dstsize)
		dst[i] = '\0';
	return (len_dst + len_src);
}
