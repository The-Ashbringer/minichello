/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:22:42 by dcarenou          #+#    #+#             */
/*   Updated: 2023/02/21 14:28:40 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = malloc((ft_strlen(s1) + 1) * sizeof(*s1));
	if (s2 == NULL)
		return (s2);
	ft_strlcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}
