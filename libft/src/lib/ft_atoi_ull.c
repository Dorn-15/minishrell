/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ull.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:47:01 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/19 17:28:36 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

unsigned long long	ft_atoi_ull(const char *str)
{
	unsigned long long	result;
	int					sign;
	int					digit;

	result = 0;
	sign = 1;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str) && result < LLONG_MAX)
	{
		digit = *str - '0';
		if (result > (ULLONG_MAX - digit) / 10)
			result = ULLONG_MAX;
		result = result * 10 + digit;
		str++;
	}
	result *= sign;
	return (result);
}
