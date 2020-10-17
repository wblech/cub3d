/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:29:40 by wbertoni          #+#    #+#             */
/*   Updated: 2020/01/27 18:32:26 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Count how many rows the tab will have
** Return: An int with the total oh rows
*/

static	int		counterow(char *cpy, char c)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	if (!cpy[i])
		return (0);
	if (ft_strchr(cpy, c) == NULL)
		return (1);
	while (cpy[i])
	{
		if (cpy[i] == c && cpy[i + 1] != c && cpy[i + 1] != '\0')
			counter++;
		i++;
	}
	return (counter + 1);
}

/*
** Get the string until find the set char
** Return: The string that it found
*/

static	char	*splitstr(char *src, char c)
{
	char	*dst;
	size_t	dstsize;
	int		i;

	i = 0;
	while (src[i] != c && src[i])
		i++;
	dst = (char *)malloc(i * sizeof(char));
	dstsize = i + 1;
	ft_strlcpy(dst, src, dstsize);
	return (dst);
}

/*
** Free the allocation made for the tab
** Return: Nothing
*/

static	void	freetab(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
}

/*
** Put the string inside tab
** Return: The tab with all the strings inside.
*/

static	char	**createtab(char **tab, char *cpy, char c, int rows)
{
	int		i;
	char	*set;

	i = 0;
	set = ft_chartostr(c);
	while (cpy && i < rows)
	{
		tab[i] = ft_strdup(splitstr(cpy, c));
		if (tab[i] == NULL)
		{
			freetab(tab, i);
			return (NULL);
		}
		cpy = ft_strchr(cpy, c);
		if (cpy != NULL)
			cpy = ft_strtrim(cpy, (char const *)set);
		i++;
	}
	tab[i] = (char *)'\0';
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	char	*cpy;
	char	*set;
	char	**tab;
	int		i;
	int		rows;

	i = 0;
	rows = 0;
	if (s == NULL)
		return (NULL);
	set = ft_chartostr(c);
	cpy = ft_strtrim(s, (char const *)set);
	if (cpy == NULL)
		return (NULL);
	rows = counterow(cpy, c);
	tab = (char **)malloc((rows + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = createtab(tab, cpy, c, rows);
	if (tab == NULL)
		return (NULL);
	return (tab);
}
