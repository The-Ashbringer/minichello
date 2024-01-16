/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:32:11 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/19 11:26:49 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*cnt;

	cnt = malloc(sizeof(*cnt));
	if (!cnt)
		return (NULL);
	cnt->content = content;
	cnt->next = NULL;
	return (cnt);
}
