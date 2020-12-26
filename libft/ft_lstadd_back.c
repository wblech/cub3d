/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:56:49 by wbertoni          #+#    #+#             */
/*   Updated: 2020/01/30 11:19:17 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *begin;

	if ((*lst) != NULL)
	{
		begin = (*lst);
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
	else
		(*lst) = new;
}
