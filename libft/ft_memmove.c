/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:44:16 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/15 11:57:33 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;

	i = 0;
	if (((dst == NULL) && (src == NULL)) || (len == 0))
		return (dst);
	if (dst > src)
	{
		i = len - 1;
		while (i > 0)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i--;
		}
		((unsigned char *)dst)[0] = ((unsigned char *)src)[0];
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}
