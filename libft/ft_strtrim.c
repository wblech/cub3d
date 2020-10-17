/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:13:40 by wbertoni          #+#    #+#             */
/*   Updated: 2020/01/30 15:43:42 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_findchar(const char *set, char c)
{
	int i;

	i = 0;
	while ((char)set[i])
	{
		if ((char)set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int		ft_start(char const *s1, char const *set, int i)
{
	while (ft_findchar(set, (char)s1[i]))
		i++;
	return (i);
}

static	int		ft_end(char const *s1, char const *set, int i)
{
	while (ft_findchar(set, (char)s1[i]))
		i--;
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	int		lstindex;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = ft_start(s1, set, 0);
	if (i != ft_strlen(s1))
	{
		lstindex = ft_end(s1, set, ft_strlen(s1) - 1);
		cpy = ft_substr(s1, i, (lstindex - i) + 1);
		if (cpy == NULL)
			return (NULL);
	}
	else
	{
		cpy = (char *)ft_calloc(1, 1 * sizeof(char));
		if (cpy == NULL)
			return (NULL);
	}
	return (cpy);
}
