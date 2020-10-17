/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 18:04:54 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/08 16:56:05 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

static char	*ft_spacelloc(size_t count, size_t size)
{
	char *ptr;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
		return (NULL);
	if (count != 0)
		ft_memset(ptr, ' ', (count - 1) * size);
	else
		ft_memset(ptr, ' ', count * size);
	return (ptr);
}

char		**ft_malloc_map(int row, int col)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = (char **)malloc((row + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < row)
	{
		ptr[i] = (char *)ft_spacelloc(col + 1, sizeof(char));
		if (!ptr[i])
			return (NULL);
		i++;
	}
	ptr[row] = NULL;
	return (ptr);
}
