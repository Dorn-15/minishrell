/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:14:12 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/17 11:39:04 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	str_isdigit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	exit_cmd(char **arg)
{
	if (!arg || !arg[0] || (arg[0] && !arg[1]))
	{
		ft_putstr_fd("exit\n", 1);
		mem_exit(0);
	}
	if (str_isdigit(arg[1]) != 0)
	{
		ft_putstr_fd("exit\nbash: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		mem_exit(2);
	}
	else if (arg[2])
	{
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
		return (1);
	}
	ft_putstr_fd("exit\n", 1);
	mem_exit(ft_atoi(arg[1]));
}
