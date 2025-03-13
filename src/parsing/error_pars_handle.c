/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:48:15 by altheven          #+#    #+#             */
/*   Updated: 2025/03/13 09:20:11 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*error_pars(int n, char **split_arg, char *tk_str, t_alloc *mem)
{
	if (tk_str)
		free(tk_str);
	if (split_arg)
		ft_freetab(split_arg);
	if (n == 1)
		write(2, "Minishell : Invalid Syntax\n", 28);
	mem->exit_status = 2;
	return (NULL);
}

int	error_invalid_files(char *str, t_alloc *mem)
{
	ft_putstr_fd("Minishell :", 2);
	ft_putstr_fd(" no such file or directory:", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	mem->exit_status = 126;
	return (1);
}
