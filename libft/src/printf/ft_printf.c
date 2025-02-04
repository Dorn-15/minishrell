/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:32:11 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 14:34:32 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	convertor_def(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = ft_print_char(va_arg(args, int));
	else if (c == 'd' || c == 'i')
		len = ft_print_nbr(va_arg(args, int));
	else if (c == 's')
		len = ft_print_str(va_arg(args, char *));
	else if (c == 'p')
		len = ft_print_address(va_arg(args, void *));
	else if (c == 'u')
		len = ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		len = ft_print_hex(va_arg(args, unsigned int), c);
	else if (c == '%')
		len = ft_print_char('%');
	else
		return (-1);
	return (len);
}

int	process_format(const char *format, va_list args)
{
	size_t	i;
	int		printed_char;
	int		conv_result;

	i = 0;
	printed_char = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			conv_result = convertor_def(format[++i], args);
			if (conv_result == -1)
				return (-1);
			printed_char += conv_result;
		}
		else if (format[i] != '%')
		{
			ft_putchar_fd(format[i], 1);
			printed_char++;
		}
		else
			return (-1);
		i++;
	}
	return (printed_char);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	if (!format)
		return (-1);
	va_start(args, format);
	result = process_format(format, args);
	va_end(args);
	return (result);
}
