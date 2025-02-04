/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:58:09 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:20:15 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Outputs the integer n to the file descriptor fd */
void	ft_print_nb(long nb, int fd)
{
	if (nb / 10)
		ft_print_nb(nb / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	ft_print_nb(nb, fd);
}
