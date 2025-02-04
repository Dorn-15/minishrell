/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:34:24 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:19:37 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Sets n bytes of memory at dest to zero */
void	ft_bzero(void *dest, size_t n)
{
	ft_memset(dest, 0, n);
}
