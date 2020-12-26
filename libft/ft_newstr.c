/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:35:54 by wbertoni          #+#    #+#             */
/*   Updated: 2020/02/04 13:50:17 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Creates a string with the length size. The function already add the '\0'
** The size should only be related with the string.
** Return: a string with '\0' in all spaces. *
*/

char	*ft_newstr(int len)
{
	char *str;

	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}
