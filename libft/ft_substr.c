/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:12:34 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/16 21:57:41 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	subs = ft_calloc((len + 1), sizeof(*subs));
	if (!subs)
		return (NULL);
	if (len <= 0)
		return (subs);
	ft_strlcpy(subs, &s[start], len + 1);
	return (subs);
}
