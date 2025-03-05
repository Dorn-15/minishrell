/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_pars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:03:29 by altheven          #+#    #+#             */
/*   Updated: 2025/03/05 21:09:06 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_if_repo(char *str, t_alloc *mem)
{
	struct stat	file;

	if (str && (str[0] == '.' || str[0] == '/'))
	{
		if (str[0] == '.' && !str[1])
		{
			ft_putstr_fd("Minishell = . filename argument required\n", 2);
			mem->exit_status = 1;
			return (1);
		}
		if (stat(str, &file) == 0)
		{
			if (S_ISDIR(file.st_mode))
			{
				ft_putstr_fd("Minishell :", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(" is a directory\n", 2);
				mem->exit_status = 126;
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}

t_cmd	*check_special_case(t_cmd *list, t_alloc *mem)
{
	t_cmd	*start;

	start = list;
	while (list)
	{
		if (list->cmd && (!ft_strncmp(list->cmd[0], ":", 1)
				|| !ft_strncmp(list->cmd[0], "!", 1)))
			list->cmd = ft_freetab(list->cmd);
		if (list->cmd && check_if_repo(list->cmd[0], mem))
			list->cmd = ft_freetab(list->cmd);
		list = list->next;
	}
	return (start);
}
