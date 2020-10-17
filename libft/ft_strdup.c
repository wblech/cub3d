/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:46:44 by wbertoni          #+#    #+#             */
/*   Updated: 2020/01/30 20:34:42 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*cpy;

	size = ft_strlen(s1);
	cpy = (char *)malloc((size + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, s1, size + 1);
	return (cpy);
}
