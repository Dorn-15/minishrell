/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:39:54 by adoireau          #+#    #+#             */
/*   Updated: 2024/12/04 16:46:33 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

double	ft_atof(const char *str)
{
	double	num;
	double	decimal;
	int		sign;
	int		i;

	num = 0.0;
	decimal = 0.1;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		num = (num * 10.0) + (str[i++] - '0');
	if (str[i++] == '.')
	{
		while (str[i] && str[i] >= '0' && str[i] <= '9')
		{
			num = num + ((str[i++] - '0') * decimal);
			decimal *= 0.1;
		}
	}
	return (num * (double)sign);
}
