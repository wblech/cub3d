/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:52:26 by wbertoni          #+#    #+#             */
/*   Updated: 2020/02/07 15:21:53 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = (char *)ft_calloc(size, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcat(new, s1, ft_strlen(s1) + 1);
	ft_strlcat(new + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (new);
}
