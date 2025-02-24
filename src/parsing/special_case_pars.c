/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_pars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:03:29 by altheven          #+#    #+#             */
/*   Updated: 2025/02/24 10:57:33 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_if_repo(char *str, char **envp)
{
	if (str && (str[0] == '.' || str[0] == '/'))
	{
		if (str[0] == '.' && !str[1])
			return (1); //erreur a gerer : filename argument required
		if ((str[0] == '/' || (str[0] == '.' && str[1] == '/'))
			&& access(str, X_OK) != 0)
			return (1);
	}
	return (0);
}

t_cmd	*check_special_case(t_cmd *list, t_cmd *tmp, t_alloc *mem)
{
	t_cmd	*start;

	start = list;
	while (list)
	{
		if (list->cmd && !ft_strncmp(list->cmd[0], ":", 1))
			list->cmd = ft_freetab(list->cmd);
		if (list->cmd && check_if_repo(list->cmd[0], mem->env))
			list->cmd = ft_freetab(list->cmd);
		list = list->next;
	}
	return (start);
}
