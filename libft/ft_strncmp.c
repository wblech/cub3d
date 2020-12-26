/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:45:41 by wbertoni          #+#    #+#             */
/*   Updated: 2020/02/07 15:38:01 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	diff = 0;
	while (i < n && !diff && s1[i] != '\0' && s2[i] != '\0')
	{
		diff = (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n && !diff && (s1[i] == '\0' || s2[i] == '\0'))
		diff = (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (diff);
}
