/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:28:25 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/12 12:25:27 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	*tab;

	i = 0;
	tab = b;
	while (i < (int)len)
	{
		tab[i] = (unsigned char)c;
		i++;
	}
	return ((void *)tab);
}
