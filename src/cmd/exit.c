/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:14:12 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/19 17:24:50 by adoireau         ###   ########.fr       */
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

static int	exit_test_long(char *arg)
{
	if (ft_strlen(arg) > 19)
		return (1);
	if (ft_atoi_ull(arg) > LLONG_MAX)
		return (1);
	return (0);
}

static void	exit_num_err(char **arg)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	mem_exit(2);
}

static int	exit_too_many_arg(void)
{
	ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
	return (1);
}

int	exit_cmd(char **arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0] || (arg[0] && !arg[1]))
	{
		ft_putstr_fd("exit\n", 1);
		mem_exit(0);
	}
	if (arg[1][0] == '-')
		i = 1;
	if (str_isdigit(arg[1] + i) != 0)
		exit_num_err(arg);
	else if (arg[2])
		return (exit_too_many_arg());
	else if (exit_test_long(arg[1] + i) != 0)
		exit_num_err(arg);
	ft_putstr_fd("exit\n", 1);
	mem_exit(ft_atoi_uch(arg[1]));
}
