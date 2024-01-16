/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:47:48 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/12 17:10:04 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	len;

	i = 0;
	dstlen = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if ((dstsize < ft_strlen(dst)))
		return (ft_strlen(src) + dstsize);
	while (dst[dstlen] != '\0')
		dstlen++;
	while ((src[i] != '\0') && (dstlen < (dstsize - 1)))
	{
		dst[dstlen] = src[i];
		i++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (ft_strlen(src) + len);
}
