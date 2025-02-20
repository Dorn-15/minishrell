/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:48:15 by altheven          #+#    #+#             */
/*   Updated: 2025/02/20 11:09:48 by altheven         ###   ########.fr       */
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
		write(2, "Invalid Synthax\n", 17);
	mem->exit_status = 2;
	return (NULL);
}
