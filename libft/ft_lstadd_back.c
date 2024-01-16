/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:53:06 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/19 12:41:33 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastcnt;

	if (lst)
	{
		if (*lst)
		{
			lastcnt = ft_lstlast(*lst);
			lastcnt->next = new;
		}
		else
			*lst = new;
	}
}
