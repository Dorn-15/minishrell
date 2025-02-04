/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:34:27 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/30 16:12:58 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_print_base(unsigned long nbr, char *base)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (nbr >= base_len)
		ft_print_base(nbr / base_len, base);
	ft_putchar_fd(base[nbr % base_len], 1);
}
