/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:51:26 by wbertoni          #+#    #+#             */
/*   Updated: 2020/02/03 16:18:18 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cpy;

	cpy = (*lst);
	while ((*lst) != NULL)
	{
		(*lst) = cpy->next;
		del(cpy->content);
		free(cpy);
		cpy = (*lst);
	}
	lst = NULL;
}
