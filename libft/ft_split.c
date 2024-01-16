/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:50:52 by dcarenou          #+#    #+#             */
/*   Updated: 2023/06/20 17:44:44 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countstr(char const *s, char c)
{
	int	strnbr;
	int	i;
	int	start;

	strnbr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i != start && (s[i] == '\0' || s[i] == c))
			strnbr++;
	}
	return (strnbr);
}

static char	*ft_free(char **str, int flaggot)
{
	if (str[flaggot] == NULL)
	{
		while (flaggot >= 0)
		{
			free(str[flaggot--]);
		}
		free(str);
		return (NULL);
	}
	return ("ok");
}

static char	**ft_plusdeplace(char const *s, char **str, char c, int i)
{
	int	start;
	int	flaggot;

	flaggot = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i != start && (s[i] == '\0' || s[i] == c))
		{
			str[flaggot] = ft_substr(s, start, i - start);
			if (ft_free(str, flaggot) == NULL)
				return (NULL);
			flaggot++;
		}
	}
	str[flaggot] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	str = malloc((sizeof(char *)) * (ft_countstr(s, c) + 1));
	if (!str)
		return (NULL);
	return (ft_plusdeplace(s, str, c, i));
}
