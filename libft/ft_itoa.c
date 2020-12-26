/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:35:31 by wbertoni          #+#    #+#             */
/*   Updated: 2020/01/28 18:16:16 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*createstr(char *a, int n, int sign, int size)
{
	while (size >= 0)
	{
		if (sign < 0 && size == 0)
			return (a);
		a[size] = (n % 10) + 48;
		n /= 10;
		size--;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	int		nbr;
	int		sign;
	int		size;
	char	*a;

	size = 0;
	sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign = -1;
	nbr = n * sign;
	while (nbr /= 10)
		size++;
	(sign < 0) ? size++ : size;
	a = ft_newstr(size + 1);
	if (a == NULL)
		return (NULL);
	if (sign < 0)
		a[0] = '-';
	a[ft_strlen(a)] = '\0';
	n *= sign;
	return (createstr(a, n, sign, size));
}
