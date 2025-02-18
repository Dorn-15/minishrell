/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:54:16 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/18 16:03:53 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_n(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	print_args(char **arg, int start, int n)
{
	int	i;

	i = start;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
}

int	echo_cmd(char **arg)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (!arg || !arg[0])
		return (0);
	while (arg[i] && is_n(arg[i]))
	{
		n = 1;
		i++;
	}
	print_args(arg, i, n);
	return (0);
}
