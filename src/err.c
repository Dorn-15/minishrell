/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:15:38 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 17:28:49 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_no_such_file(char *cmd, char *arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': no such file or directory\n", 2);
}
void	put_permission_denied(char *cmd, char *arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': permission denied\n", 2);
}

void	put_invalid_option(char *cmd, char arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": invalid option -- '", 2);
	ft_putchar_fd(arg, 2);
	ft_putstr_fd("'\n", 2);
}

void	put_unrecognized_option(char *cmd, char *arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": unrecognized option '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("'\n", 2);
}
