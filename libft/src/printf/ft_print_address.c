/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:53:14 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/30 16:13:01 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_print_address(void *ptr)
{
	unsigned long	address;
	int				len;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	address = (unsigned long)ptr;
	ft_putstr_fd("0x", 1);
	ft_print_base(address, "0123456789abcdef");
	len = 2;
	while (address)
	{
		len++;
		address /= 16;
	}
	return (len);
}
