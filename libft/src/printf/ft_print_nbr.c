/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:51:51 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 14:34:48 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar_fd((n % 10) + '0', 1);
}

int	ft_print_nbr(int n)
{
	int	len;
	int	tmp;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	len = 0;
	if (n <= 0)
		len = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n = -n;
	}
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	ft_putnbr(n);
	return (len);
}
