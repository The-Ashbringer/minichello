/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:25:21 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/16 18:26:53 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(int nbr)
{
	int	i;

	i = 0;
	if (nbr <= 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*str;

	i = ft_count(n);
	str = malloc(i + 1);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[i] = '\0';
	i--;
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		if (n > 0)
			str[i] = n % 10 + 48;
		if (n < 0)
			str[i] = ((n % 10) * -1 + 48);
		n = n / 10;
		i--;
	}
	return (str);
}
