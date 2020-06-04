/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:30:54 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/02 12:38:53 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t i;
// 	size_t len;

// 	if (dst == 0 || src == 0)
// 		return (0);
// 	len = 0;
// 	while (dst != src && src[len] != '\0')
// 		len++;
// 	i = 0;
// 	while (dst != src && dstsize && src[i] != '\0' && (i < (dstsize - 1)))
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	if (dstsize != 0)
// 		dst[i] = '\0';
// 	return (len);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*new;
// 	size_t	size;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	size = ft_strlen_char(s1, '\0') + (ft_strlen_char(s2, '\0')) + 1;
// 	new = (char *)malloc(size * sizeof(char));
// 	if (new == NULL)
// 		return (NULL);
// 	ft_strlcpy(new, s1, ft_strlen_char(s1, '\0') + 1);
// 	ft_strlcpy(new + ft_strlen_char(s1, '\0'), s2, ft_strlen_char(s2,
// 				'\0') + 1);
// 	return (new);
// }

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

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*sub;

// 	if (s == NULL)
// 		return (NULL);
// 	sub = (char *)malloc((len + 1) * sizeof(char));
// 	if (sub == NULL)
// 		return (NULL);
// 	if ((unsigned int)ft_strlen_char(s, '\0') < start)
// 	{
// 		sub[0] = '\0';
// 		return (sub);
// 	}
// 	ft_strlcpy(sub, (s + start), len + 1);
// 	return (sub);
// }
