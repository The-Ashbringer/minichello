/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:06:10 by dcarenou          #+#    #+#             */
/*   Updated: 2023/02/21 14:21:37 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formats(va_list args, const char format)
{
	int	print_len;

	print_len = 0;
	if (format == 'c')
		print_len += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_len += ft_pourcentage_s(va_arg(args, char *));
	else if (format == 'p')
		print_len += ft_pourcentage_p(va_arg(args, unsigned long int));
	else if (format == 'd' || format == 'i')
		print_len += ft_pourcentage_d_i(va_arg(args, int));
	else if (format == 'u')
		print_len += ft_pourcentage_u(va_arg(args, unsigned int));
	else if (format == 'x')
		print_len += ft_pourcentage_x(va_arg(args, unsigned int));
	else if (format == 'X')
		print_len += ft_pourcentage_upper_x(va_arg(args, unsigned int));
	else if (format == '%')
		print_len += ft_printchar('%');
	return (print_len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		print_len;
	va_list	args;

	i = 0;
	print_len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			print_len += ft_formats(args, format[i + 1]);
			i++;
		}
		else
			print_len += ft_printchar(format[i]);
		i++;
	}
	va_end(args);
	return (print_len);
}
