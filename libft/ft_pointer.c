/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:58:29 by dcarenou          #+#    #+#             */
/*   Updated: 2023/02/21 14:21:31 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pourcentage_p(unsigned long int nb)
{
	write (1, "0x", 2);
	if (nb == 0)
	{
		write(1, "0", 1);
		return (3);
	}
	return (2 + (ft_pourcentage_xp(nb)));
}

int	ft_pourcentage_xp(unsigned long int nb)
{
	if (nb == 0)
		return (0);
	return ((ft_pourcentage_xp(nb / 16)) + (ft_hexa_p(nb % 16)));
}

int	ft_hexa_p(unsigned long int reste)
{
	char	*base;

	base = "0123456789abcdef";
	return (ft_printchar(base[reste]));
}
