/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:06:54 by dcarenou          #+#    #+#             */
/*   Updated: 2023/02/21 14:21:16 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pourcentage_d_i(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (nb >= 0 && nb <= 9)
		return (ft_printchar(nb + '0'));
	else if (nb < 0)
	{
		ft_printchar('-');
		return (1 + ft_pourcentage_d_i(nb * (-1)));
	}
	else
		return (ft_pourcentage_d_i(nb / 10) + ft_printchar((nb % 10) + '0'));
}

int	ft_pourcentage_u(unsigned int nb)
{
	if (nb >= 0 && nb <= 9)
		return (ft_printchar(nb + '0'));
	else
		return ((ft_pourcentage_u(nb / 10)) + (ft_printchar((nb % 10) + '0')));
}
