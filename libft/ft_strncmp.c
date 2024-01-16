/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:29 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/21 19:05:48 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0'))
			i++;
		else
			return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
	}
	return (0);
}
