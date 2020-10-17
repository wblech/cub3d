/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:30:54 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/17 19:13:28 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

int		ft_strlen_char(const char *str, char c)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	if (c == '\0')
	{
		while (str[i] != '\0')
			i++;
	}
	else
	{
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (i);
}

char	*ft_haschr(const char *s, int c)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while ((char)s[i] != '\0')
	{
		if ((char)s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
