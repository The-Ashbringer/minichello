/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:58:47 by dcarenou          #+#    #+#             */
/*   Updated: 2022/11/21 19:06:22 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*check;

	check = malloc(count * size);
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	if (check == 0)
		return (0);
	ft_memset(check, 0, count * size);
	return (check);
}
