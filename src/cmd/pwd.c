/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:58:33 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/17 15:07:57 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	pwd_err_access(void)
{
	ft_putstr_fd("pwd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	return (1);
}

static int	pwd_err_options(char arg)
{
	ft_putstr_fd("bash: pwd: -", 2);
	ft_putchar_fd(arg, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("pwd: usage: pwd [no options]\n", 2);
	return (2);
}

int	pwd_cmd(char **arg)
{
	char	cwd[PATH_MAX];

	if (!arg && !arg[0])
		return (0);
	else if (arg[1] && arg[1][0] == '-'
			&& ((arg[1][1] && arg[1][1] != '-')
			|| (arg[1][1] == '-' && arg[1][2])))
		return (pwd_err_options(arg[1][1]));
	else if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (pwd_err_access());
	printf("%s\n", cwd);
	return (0);
}
