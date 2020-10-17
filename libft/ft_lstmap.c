/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 18:19:20 by wbertoni          #+#    #+#             */
/*   Updated: 2020/02/05 14:19:39 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		lstsize(t_list *lst)
{
	int count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

static	t_list	*lstnew(void *content)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

static	void	lstadd_back(t_list **lst, t_list *new)
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

static	void	lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*x;

	while (*lst)
	{
		x = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = x;
	}
	lst = NULL;
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*new;
	int		size;

	size = 0;
	begin = NULL;
	if (lst == NULL)
		return (NULL);
	size = lstsize(lst);
	while (size--)
	{
		new = lstnew(f(lst->content));
		if (new != NULL)
			lstadd_back(&begin, new);
		else
		{
			lstclear(&begin, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (begin);
}
