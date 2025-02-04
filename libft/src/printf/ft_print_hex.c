/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:34:27 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 14:34:51 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_print_hex(unsigned int n, char format)
{
	int				len;
	unsigned int	tmp;
	char			*base;

	base = "0123456789ABCDEF";
	if (format == 'x')
		base = "0123456789abcdef";
	len = 0;
	tmp = n;
	if (n == 0)
		len = 1;
	while (tmp)
	{
		tmp /= 16;
		len++;
	}
	ft_print_base(n, base);
	return (len);
}
