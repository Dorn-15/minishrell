/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_err_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:40:06 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/18 14:38:39 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	cd_invalid_option(char c)
{
	ft_putstr_fd("bash: cd: -", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (2);
}

int	cd_permission_denied(char *arg)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": permission denied\n", 2);
	return (1);
}

int	cd_too_many_links(char *arg)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": too many links\n", 2);
	return (1);
}

int	cd_no_such_file(char *arg)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
	return (1);
}

int	cd_not_a_directory(char *arg)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a directory\n", 2);
	return (1);
}
