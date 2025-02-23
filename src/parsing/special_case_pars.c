/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_pars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:03:29 by altheven          #+#    #+#             */
/*   Updated: 2025/02/23 17:47:57 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void t_cmd	*delone_list(t_cmd *list)
// {
// 	if (list->cmd)
// 		ft_freetab(list->cmd);
// 	if (list->limiter)
// 		ft_freetab(list->limiter);
// 	if (list->fd_in != 0)
// 		close(list->fd_in);
// 	if (list->fd_out != 1)
// 		close(list->fd_out);
// 	free(list);
// 	return (NULL);
// }

t_cmd	*check_special_case(t_cmd *list, t_cmd *tmp)
{
	t_cmd	*start;

	start = list;
	while (list)
	{
		if (list->cmd && !ft_strncmp(list->cmd[0], ":", 1))
			list->cmd = ft_freetab(list->cmd);
		list = list->next;
	}
	return (start);
}
