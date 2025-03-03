/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:15:38 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/03 20:41:08 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	env_no_such_file(char *arg)
{
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': no such file or directory\n", 2);
}

void	env_permission_denied(char *arg)
{
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': permission denied\n", 2);
}

void	env_invalid_option(char arg)
{
	ft_putstr_fd("env: invalid option -- '", 2);
	ft_putchar_fd(arg, 2);
	ft_putstr_fd("'\n", 2);
}

void	env_unrecognized_option(char *arg)
{
	ft_putstr_fd("env: unrecognized option '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("'\n", 2);
}

void	env_no_arg(char *arg)
{
	ft_putstr_fd("env: invalid arguments ´", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("'\nenv: usage: env [no args]\n", 2);
}
