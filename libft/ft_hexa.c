/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:53:58 by dcarenou          #+#    #+#             */
/*   Updated: 2023/02/21 14:21:10 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pourcentage_x(unsigned int nb)
{
	if (nb <= 15)
		return (ft_hexa_lower(nb));
	else
		return ((ft_pourcentage_x(nb / 16)) + (ft_hexa_lower(nb % 16)));
}

int	ft_pourcentage_upper_x(unsigned int nb)
{
	if (nb <= 15)
		return (ft_hexa_upper(nb));
	else
		return ((ft_pourcentage_upper_x(nb / 16)) + (ft_hexa_upper(nb % 16)));
}

int	ft_hexa_lower(unsigned int reste)
{
	char	*base;

	base = "0123456789abcdef";
	return (ft_printchar(base[reste]));
}

int	ft_hexa_upper(unsigned int reste)
{
	char	*base;

	base = "0123456789ABCDEF";
	return (ft_printchar(base[reste]));
}
