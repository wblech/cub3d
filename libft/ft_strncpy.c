/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:42:10 by wbertoni          #+#    #+#             */
/*   Updated: 2020/01/28 18:49:55 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int i;

	i = 0;
	while (len && src[i])
	{
		dst[i] = src[i];
		i++;
		len--;
	}
	while (len && dst[i])
	{
		dst[i] = '\0';
		len--;
		i++;
	}
	return (dst);
}
