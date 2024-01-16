/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcareniy <dcareniy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:22:52 by dcarenou          #+#    #+#             */
/*   Updated: 2023/05/05 00:49:15 by dcareniy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*chaystack;

	i = 0;
	j = 0;
	chaystack = ((char *)haystack);
	if (needle[0] == '\0' || (len == 0 && chaystack == NULL))
		return (chaystack);
	while (i < len && chaystack[i])
	{
		if (chaystack[i] == needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return (&chaystack[i - j + 1]);
		}
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}
