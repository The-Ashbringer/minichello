/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:52:03 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/20 19:26:58 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*firstlst;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	if (newlst == NULL)
		return (NULL);
	firstlst = newlst;
	lst = lst->next;
	while (lst)
	{
		newlst->next = ft_lstnew(f(lst->content));
		if (!(newlst -> next))
		{
			ft_lstclear(&firstlst, del);
			return (NULL);
		}
		lst = lst->next;
		newlst = newlst->next;
	}
	return (firstlst);
}
