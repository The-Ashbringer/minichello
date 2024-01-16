/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:37:56 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/20 21:26:25 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itsthefirstcountdown(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	isok;

	i = 0;
	isok = 1;
	while (s1[i] && isok)
	{
		j = 0;
		isok = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				isok = 1;
			j++;
		}
		if (isok)
			i++;
	}
	return (i);
}

static int	ft_itsthefinalcountdown(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	isok;

	i = ft_strlen(s1) - 1;
	isok = 1;
	while (i >= 0 && isok)
	{
		j = 0;
		isok = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				isok = 1;
			j++;
		}
		if (isok == 1)
			i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!s1 || !set)
		return (NULL);
	i = ft_itsthefirstcountdown(s1, set);
	j = ft_itsthefinalcountdown(s1, set);
	len = j - i;
	if (len <= 0)
	{
		len = 0;
		str = malloc(sizeof(char) * (len + 1));
	}
	else
		str = malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &(s1[i]), len + 2);
	return (str);
}
