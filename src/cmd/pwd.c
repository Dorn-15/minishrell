/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:58:33 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 10:01:49 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pwd_cmd(char **env, char *arg)
{
	char	cwd[PATH_MAX];

	if (arg && arg[0] == '-')
	{
		if ((arg[1] && arg[1] != '-') || (arg[1] == '-' && arg[2]))
		{
			ft_putstr_fd("pwd: -", 2);
			ft_putchar_fd(arg[1], 2);
			ft_putstr_fd(" : option non valable\n", 2);
			ft_putstr_fd("pwd : utilisation :pwd [-LP]\n", 2);
			mem_exit(2);
		}
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		mem_exit(0);
	}
	else
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		mem_exit(1);
	}
}
